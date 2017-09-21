/**
* �X�L�����b�V���m�[�h�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkSkinMeshNode.h"

namespace nkEngine
{

	namespace
	{

		//�l�p�|���S�����O�p�|���S���ɕϊ�����l.
		static const UINT IndexArray4[6] = { 3, 2, 0, 2, 1, 0 };
		static const UINT IndexArray3[3] = { 2, 1, 0 };

		/**
		* �e�N�X�`���������.
		*/
		string TextureNameSearch(const string& str)
		{
			stringstream ss(str);
			string buffer;
			while (getline(ss, buffer, '\\'));
			return buffer;
		}


	}


	/**
	* �쐬.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	* @param parent		�e�̃|�C���^.
	* @param modelData	���f���f�[�^.
	*/
	void SkinMeshNode::Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)
	{
		//���b�V���^�C�v�ɐݒ�.
		NodeType_ = NodeTypeE::SkinMesh;

		//���_�o�b�t�@���쐬.
		CreateVertexBuffer(fbxNode->GetMesh(), modelData);

		//�}�e���A���̍쐬.
		CreateMaterial(fbxNode, modelData);

		INode::Create(fbxNode, parent, modelData);
	}

	/**
	* �`��.
	*/
	void SkinMeshNode::Render()
	{
		//���_�o�b�t�@��ݒ�.
		Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		//Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		//�`��B
		Engine().GetRenderContext().Draw(VertexCount_, 0);
	}

	/**
	* ���_�o�b�t�@�̍쐬.
	*/
	void SkinMeshNode::CreateVertexBuffer(FbxMesh * fbxMesh, ModelData* modelData)
	{
		//���_�o�b�t�@�̃\�[�X�f�[�^.
		vector<VertexBufferS> vertexList;

		//���_���W���X�g.
		FbxVector4* pVertex = fbxMesh->GetControlPoints();

		Matrix mTmp = Matrix::FbxToMatrix(fbxMesh->GetNode()->EvaluateGlobalTransform());

		FbxStringList lUVSetNameList;
		fbxMesh->GetUVSetNames(lUVSetNameList);
		for (int i = 0; i < lUVSetNameList.GetCount(); i++)
		{
			FbxString name = lUVSetNameList[i];
			UVSetNameList_.push_back(name.Buffer());
		}

		//�|���S�����J��Ԃ�.
		for (int i = 0; i < fbxMesh->GetPolygonCount(); i++)
		{
			//�|���S���T�C�Y.
			int numVertex = fbxMesh->GetPolygonSize(i);

			switch (numVertex)
			{
				case 3:
				{
					for (int j = 0; j < 3; j++)
					{
						//���_.
						VertexBufferS vertex;

						//���_���W�C���f�b�N�X.
						int cpIndex = fbxMesh->GetPolygonVertex(i, IndexArray3[j]);
						Vector3 pos = Vector3(-pVertex[cpIndex].mData[0], pVertex[cpIndex].mData[1], pVertex[cpIndex].mData[2]);
						pos.TransformCoord(mTmp);
						//���_���W��ݒ�.
						vertex.Pos.Set(pos);
						VertexPosList_.push_back(pos);

						//�@��.
						FbxVector4 FBXnormal;
						fbxMesh->GetPolygonVertexNormal(i, IndexArray3[j], FBXnormal);
						Vector3 normal = Vector3(-FBXnormal.mData[0], FBXnormal.mData[1], FBXnormal.mData[2]);
						normal.TransformCoord(mTmp);
						//�@����ݒ�.
						vertex.Normal = normal;

						//UV�ݒ�
						FbxVector2 textureUV;
						bool isMapped;
						fbxMesh->GetPolygonVertexUV(i, IndexArray3[j], UVSetNameList_[0].c_str(), textureUV, isMapped);
						vertex.Tex = Vector2(textureUV[0], -textureUV[1]);

						vertexList.push_back(vertex);
					}
					break;
				}
				case 4:
				{
					for (int j = 0; j < 6; j++)
					{
						//���_.
						VertexBufferS vertex;

						//���_���W�C���f�b�N�X.
						int cpIndex = fbxMesh->GetPolygonVertex(i, IndexArray4[j]);
						Vector3 pos = Vector3(-pVertex[cpIndex].mData[0], pVertex[cpIndex].mData[1], pVertex[cpIndex].mData[2]);
						pos.TransformCoord(mTmp);
						//���_���W��ݒ�.
						vertex.Pos.Set(pos);
						VertexPosList_.push_back(pos);

						//�@��.
						FbxVector4 FBXnormal;
						fbxMesh->GetPolygonVertexNormal(i, IndexArray4[j], FBXnormal);
						Vector3 normal = Vector3(-FBXnormal.mData[0], FBXnormal.mData[1], FBXnormal.mData[2]);
						normal.TransformCoord(mTmp);
						//�@����ݒ�.
						vertex.Normal = normal;

						//UV�ݒ�
						FbxVector2 textureUV;
						bool isMapped;
						fbxMesh->GetPolygonVertexUV(i, IndexArray4[j], UVSetNameList_[0].c_str(), textureUV, isMapped);
						vertex.Tex = Vector2(textureUV[0], -textureUV[1]);

						vertexList.push_back(vertex);
					}
					break;
				}
			}
		}

		//���_�����擾.
		VertexCount_ = vertexList.size();

		//�ڃx�N�g�����v�Z.
		CreateTanget(vertexList);

		//�X�L���N���X.
		FbxSkin* FBXSkin = nullptr;
		UINT deformerCount = fbxMesh->GetDeformerCount();
		for (int i = 0; i < deformerCount; i++)
		{
			FbxDeformer* FBXDeformer = fbxMesh->GetDeformer(i);
			if (FBXDeformer->GetDeformerType() == FbxDeformer::eSkin)
			{
				//FBX�X�L���N���X�Ƀ_�E���L���X�g.
				FBXSkin = (FbxSkin*)FBXDeformer;
			}
		}

		vector<VertexBoneS> VertexBoneList;
		VertexBoneList.resize(VertexCount_);

		if (FBXSkin != nullptr)
		{
			//�{�[����.
			int boneCount = FBXSkin->GetClusterCount();
			for (int i = 0; i < boneCount; i++)
			{
				FbxCluster* FBXBone = FBXSkin->GetCluster(i);

				//�{�[����.
				string BoneName(FBXBone->GetLink()->GetName());
				//�{�[���C���f�b�N�X.
				UINT boneIndex = modelData->GetSkeleton()->FindBoneIndex(BoneName);

				fbxsdk::FbxAMatrix FBXinitMat;
				FBXBone->GetTransformLinkMatrix(FBXinitMat);
				Matrix mat = Matrix::FbxToMatrix(FBXinitMat);
				modelData->GetSkeleton()->FindBone(BoneName)->SetBoneOffsetMatrix(mat);

				switch (FBXBone->GetLinkMode())
				{
					case FbxCluster::eNormalize:
						/**
						* �E�F�C�g�̍��v��1.0�ɂȂ��Ă���Ă�.
						*/
					{
						//���̃{�[���ɂ���Ĉړ����钸�_�̐�.
						int boneIndexCount = FBXBone->GetControlPointIndicesCount();

						int* Index = FBXBone->GetControlPointIndices();

						double* boneWeight = FBXBone->GetControlPointWeights();

						for (int j = 0; j < boneIndexCount; j++)
						{
							VertexBoneList[Index[j]].Bone_.push_back(BoneS(boneIndex, boneWeight[j]));
						}
						break;
					}
					case FbxCluster::eAdditive:
					{
						NK_ASSERT(false, "eAdditive������.");
						break;
					}
					case FbxCluster::eTotalOne:
					{
						NK_ASSERT(false, "eTotalOne������.");
						break;
					}
				}

			}
		}

		for (auto& it : VertexBoneList)
		{
			sort(it.Bone_.begin(), it.Bone_.end(), [](BoneS bone0, BoneS bone1)
			{
				return bone0.BoneWeight_ > bone1.BoneWeight_;
			});
		}

		for (int i = 0;i < VertexCount_;i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j < VertexBoneList[i].Bone_.size())
				{
					vertexList[i].BoneIndex_[j] = VertexBoneList[i].Bone_[j].BoneIndex_;
					vertexList[i].BoneWeight_[j] = VertexBoneList[i].Bone_[j].BoneWeight_;
				}
				else
				{
					vertexList[i].BoneIndex_[j] = 0;
					vertexList[i].BoneWeight_[j] = 0.0f;
				}
			}
		}

		//�{�[�����X�g�����.
		for (auto& it : VertexBoneList)
		{
			it.Bone_.clear();
		}
		VertexBoneList.clear();

		//���_�o�b�t�@.
		VertexBuffer_.Create(vertexList.data(), VertexCount_, sizeof(VertexBufferS));

		vertexList.clear();
	}

	/**
	* �ڃx�N�g�����쐬.
	*
	* @param vertexList	���_���X�g.
	*/
	void SkinMeshNode::CreateTanget(vector<VertexBufferS>& vertexList)
	{
		//�ڃx�N�g�������߂�.
		for (int i = 0; i < VertexCount_;)
		{
			Vector3 CP0[3] =
			{
				Vector3(vertexList[i].Pos.x, vertexList[i].Tex.x, vertexList[i].Tex.y),
				Vector3(vertexList[i].Pos.y, vertexList[i].Tex.x, vertexList[i].Tex.y),
				Vector3(vertexList[i].Pos.z, vertexList[i].Tex.x, vertexList[i].Tex.y),
			};
			Vector3 CP1[3] =
			{
				Vector3(vertexList[i + 1].Pos.x, vertexList[i + 1].Tex.x, vertexList[i + 1].Tex.y),
				Vector3(vertexList[i + 1].Pos.y, vertexList[i + 1].Tex.x, vertexList[i + 1].Tex.y),
				Vector3(vertexList[i + 1].Pos.z, vertexList[i + 1].Tex.x, vertexList[i + 1].Tex.y),
			};
			Vector3 CP2[3] =
			{
				Vector3(vertexList[i + 2].Pos.x, vertexList[i + 2].Tex.x, vertexList[i + 2].Tex.y),
				Vector3(vertexList[i + 2].Pos.y, vertexList[i + 2].Tex.x, vertexList[i + 2].Tex.y),
				Vector3(vertexList[i + 2].Pos.z, vertexList[i + 2].Tex.x, vertexList[i + 2].Tex.y),
			};

			//�ڃx�N�g��.
			float U[3];
			for (int j = 0; j < 3; j++)
			{
				Vector3 V1, V2, ABC;
				V1.Sub(CP1[j], CP0[j]);
				V2.Sub(CP2[j], CP1[j]);

				ABC.Cross(V1, V2);

				U[j] = -ABC.y / ABC.x;
			}

			vertexList[i].Tangent = Vector3(U[0], U[1], U[2]);
			vertexList[i + 1].Tangent = Vector3(U[0], U[1], U[2]);
			vertexList[i + 2].Tangent = Vector3(U[0], U[1], U[2]);

			i += 3;
		}

	}


	/**
	* �}�e���A���̍쐬.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	*/
	void SkinMeshNode::CreateMaterial(FbxNode * fbxNode, ModelData* modelData)
	{

		//�}�e���A����.
		int materialCount = fbxNode->GetMaterialCount();

		if (materialCount > 0)
		{
			FbxSurfaceMaterial* FBXMaterial = fbxNode->GetMaterial(0);

			FbxProperty prop = FBXMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

			//FbxLayeredTexture�̐�.
			int LayeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

			if (LayeredTextureCount > 0)
			{
				//--- �A�^�b�`���ꂽ�e�N�X�`���̐������J��Ԃ� ---//
				for (int j = 0; LayeredTextureCount > j; j++) {

					//--- �e�N�X�`�����擾 ---//
					FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
					//--- ���C���[�����擾 ---//
					int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

					//--- ���C���[�������J��Ԃ� ---//
					for (int k = 0; textureCount > k; k++) {
						//--- �e�N�X�`�����擾 ---//
						FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

						if (texture)
						{
							//�e�N�X�`�������擾.
							std::string textureName = texture->GetRelativeFileName();

							textureName = TextureNameSearch(textureName);

							//--- UVSet�����擾 ---//
							std::string uvSetName = texture->UVSet.Get().Buffer();

							//--- UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ� ---//
							for (auto& it : UVSetNameList_)
							{
								if (it == uvSetName)
								{
									bool isTexture = false;
									int materialNum = 0;
									for (auto& it : modelData->GetMaterialList())
									{
										if (it->Name_ == textureName)
										{
											isTexture = true;
											break;
										}
										materialNum++;
									}

									if (!isTexture)
									{
										Material* material = new Material();
										material->Init(textureName);
										modelData->GetMaterialList().push_back(material);
									}

									MaterialNum_ = materialNum;
								}
							}
						}
					}
				}
			}
			else
			{
				//�e�N�X�`�������擾.
				int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

				if (0 < fileTextureCount)
				{
					FbxFileTexture* FBXTexture = prop.GetSrcObject<FbxFileTexture>(0);

					if (FBXTexture)
					{
						//�e�N�X�`�������擾.
						std::string textureName = FBXTexture->GetRelativeFileName();

						textureName = TextureNameSearch(textureName);

						//--- UVSet�����擾 ---//
						std::string uvSetName = FBXTexture->UVSet.Get().Buffer();

						//--- UVSet�����r���Ή����Ă���e�N�X�`���Ȃ�ێ� ---//
						for (auto& it : UVSetNameList_)
						{
							if (it == uvSetName)
							{
								bool isTexture = false;
								int materialNum = 0;
								for (auto& it : modelData->GetMaterialList())
								{
									if (it->Name_ == textureName)
									{
										isTexture = true;
										break;
									}
									materialNum++;
								}

								if (!isTexture)
								{
									Material* material = new Material();
									material->Init(textureName);
									modelData->GetMaterialList().push_back(material);
								}

								MaterialNum_ = materialNum;
							}
						}

					}
				}
			}

		}

	}
}