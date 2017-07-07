/**
* ���b�V���N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkMesh.h"

namespace nkEngine
{

	namespace
	{

		//�l�p�|���S�����O�p�|���S���ɕϊ�����l.
		static const UINT IndexArray[6] = { 0, 1, 2, 0, 2, 3 };

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
	* �ǂݍ���.
	*
	* @param fbxMesh	FBXSDK�̃��b�V���N���X.
	* @param parent		�e�̃g�����X�t�H�[���|�C���^.
	*/
	void Mesh::Load(FbxMesh * fbxMesh, Transform* parent, ModelData* modelData)
	{
		//���O���擾.
		Name_ = fbxMesh->GetNode()->GetName();
		
		//�e�̃g�����X�t�H�[����ݒ�.
		LocalTransform_.Parent_ = parent;

		//�o�b�t�@�̍쐬.
		CreateBuffer(fbxMesh);

		//�}�e���A���̍쐬.
		CreateMaterial(fbxMesh->GetNode(), modelData);
	
	}

	/**
	* �X�V.
	*/
	void Mesh::Update()
	{
		//�g�����X�t�H�[���̍X�V.
		LocalTransform_.Update();
	}

	/**
	* �`��.
	*/
	void Mesh::Render()
	{
		//���_�o�b�t�@��ݒ�.
		Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�`��B
		Engine().GetRenderContext().Draw(VertexCount_, 0);
	}

	/**
	* �o�b�t�@�̍쐬.
	*
	* @param fbxMesh	FBXSDK�̃��b�V���N���X.
	*/
	void Mesh::CreateBuffer(FbxMesh * fbxMesh)
	{
	
		//���_��.
		VertexCount_ = fbxMesh->GetControlPointsCount();

		//���_�o�b�t�@�̃\�[�X�f�[�^.
		vector<VertexBufferS> vertexTmpList;
		vertexTmpList.resize(VertexCount_);

		//���_���W��ǂݍ���.
		LoadPosition(vertexTmpList, fbxMesh);

		//�C���f�b�N�X���X�g.
		vector<USHORT> indexList;

		//�C���f�b�N�X���X�g���쐬.
		CreateIndexList(indexList, fbxMesh);

		//�@�����v�Z.
		CreateNormal(vertexTmpList, indexList);

		//���_��.
		VertexCount_ = indexList.size();
		//���_�o�b�t�@�̃\�[�X�f�[�^.
		vector<VertexBufferS> vertexList;
		vertexList.resize(VertexCount_);

		for (int i = 0; i < indexList.size(); i++)
		{
			vertexList[i].Pos = vertexTmpList[indexList[i]].Pos;
			vertexList[i].Normal = vertexTmpList[indexList[i]].Normal;
		}

		vertexTmpList.clear();

		//UV���W��ǂݍ���.
		LoadUV(vertexList, fbxMesh);

		//�ڃx�N�g�����v�Z.
		CreateTanget(vertexList);

		//���_�o�b�t�@.
		VertexBuffer_.Create(vertexList.data(), VertexCount_, sizeof(VertexBufferS));

	}

	/**
	* ���_���W��ǂݍ���.
	*
	* @param vertexList	���_���X�g.
	* @param fbxMesh	FBXSDK�̃��b�V���N���X.
	*/
	void Mesh::LoadPosition(vector<VertexBufferS>& vertexList, FbxMesh * fbxMesh)
	{
		Matrix mTmp = Matrix::FbxToMatrix(fbxMesh->GetNode()->EvaluateGlobalTransform());

		for (int i = 0; i < VertexCount_; i++)
		{
			FbxVector4 FBXVertex = fbxMesh->GetControlPointAt(i);

			Vector3 Pos = Vector3((float)FBXVertex[0], (float)FBXVertex[1], (float)FBXVertex[2]);
			Pos.TransformCoord(mTmp);

			vertexList[i].Pos = Vector4(Pos.x, Pos.y, Pos.z, 1.0f);
		}
	}

	/**
	* �C���f�b�N�X���X�g���쐬����.
	*
	* @param indexList	�C���f�b�N�X���X�g.
	* @param fbxMesh	FBXSDK�̃��b�V���N���X.
	*/
	void Mesh::CreateIndexList(vector<USHORT>& indexList, FbxMesh * fbxMesh)
	{
		//�C���f�b�N�X�o�b�t�@�̍쐬.
		int indexCount = 0;

		int polygonCount = fbxMesh->GetPolygonCount();

		for (int i = 0; i < polygonCount; i++)
		{
			int polygonSize = fbxMesh->GetPolygonSize(i);

			switch (polygonSize)
			{
			case 3:
				indexCount += 3;
				break;
			case 4:
				indexCount += 6;
				break;
			default:
				break;
			}
		}

		indexList.resize(indexCount);

		UINT Index = 0;
		for (int i = 0; i < polygonCount; i++)
		{
			// 1�|���S�����̒��_�����擾
			int lPolygonSize = fbxMesh->GetPolygonSize(i);

			switch (lPolygonSize)
			{
			case 3:  // �O�p�|���S��
				for (int j = 0; j < 3; j++)
				{
					// �R���g���[���|�C���g�̃C���f�b�N�X���擾
					indexList[Index] = fbxMesh->GetPolygonVertex(i, j);
					Index++;
				}
				break;
			case 4: // �l�p�|���S��
				for (int j = 0; j < 6; j++)
				{
					// �R���g���[���|�C���g�̃C���f�b�N�X���擾
					indexList[Index] = fbxMesh->GetPolygonVertex(i, IndexArray[j]);
					Index++;
				}
				break;
			}
		}

	}

	/**
	* �@�����쐬.
	*
	* @param vertexList	���_���X�g.
	* @param indexList	�C���f�b�N�X���X�g.
	*/
	void Mesh::CreateNormal(vector<VertexBufferS>& vertexList, vector<USHORT>& indexList)
	{
		for (int i = 0; i < indexList.size();)
		{
			Vector3 Pos_0 = Vector3(vertexList[indexList[i]].Pos.x, vertexList[indexList[i]].Pos.y, vertexList[indexList[i]].Pos.z);
			Vector3 Pos_1 = Vector3(vertexList[indexList[i + 1]].Pos.x, vertexList[indexList[i + 1]].Pos.y, vertexList[indexList[i + 1]].Pos.z);
			Vector3 Pos_2 = Vector3(vertexList[indexList[i + 2]].Pos.x, vertexList[indexList[i + 2]].Pos.y, vertexList[indexList[i + 2]].Pos.z);

			Vector3 Pos0To1, Pos0To2;
			Pos0To1.Sub(Pos_1, Pos_0);
			Pos0To2.Sub(Pos_2, Pos_0);

			Vector3 Normal;
			Normal.Cross(Pos0To1, Pos0To2);

			vertexList[indexList[i]].Normal.Add(Normal);
			vertexList[indexList[i + 1]].Normal.Add(Normal);
			vertexList[indexList[i + 2]].Normal.Add(Normal);

			i += 3;
		}
	}

	/**
	* �ڃx�N�g�����쐬.
	*
	* @param vertexList	���_���X�g.
	*/
	void Mesh::CreateTanget(vector<VertexBufferS>& vertexList)
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
	* UV���W��ǂݍ���.
	*/
	void Mesh::LoadUV(vector<VertexBufferS>& vertexList, FbxMesh * fbxMesh)
	{
		int polygonCount = fbxMesh->GetPolygonCount();

		//UV���W��ݒ�.
		FbxLayerElementUV* FBXLayerUV = fbxMesh->GetLayer(0)->GetUVs();

		if (FBXLayerUV)
		{
			if (FBXLayerUV->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
			{
				if (FBXLayerUV->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				{
					int uvIndex = 0;
					int offset = 0;
					for (int i = 0; i < polygonCount; i++)
					{
						// 1�|���S�����̒��_�����擾
						int lPolygonSize = fbxMesh->GetPolygonSize(i);
						switch (lPolygonSize)
						{
						case 3:
						{
							for (int j = 0; j < 3; j++)
							{
								int index = FBXLayerUV->GetIndexArray().GetAt(j + offset);
								FbxVector2 FBXTex = FBXLayerUV->GetDirectArray().GetAt(index);
								vertexList[uvIndex].Tex = Vector2(FBXTex[0], 1.0f - FBXTex[1]);
								uvIndex++;
							}
						}
						break;
						case 4:
						{
							for (int j = 0; j < 6; j++)
							{
								int index = FBXLayerUV->GetIndexArray().GetAt(IndexArray[j] + offset);
								FbxVector2 FBXTex = FBXLayerUV->GetDirectArray().GetAt(index);
								vertexList[uvIndex].Tex = Vector2(FBXTex[0], 1.0f - FBXTex[1]);
								uvIndex++;
							}
						}
						break;
						}
						offset += lPolygonSize;
					}
				}
			}
			else if (FBXLayerUV->GetMappingMode() == FbxLayerElement::eByControlPoint)
			{
				if (FBXLayerUV->GetReferenceMode() == FbxLayerElement::eDirect)
				{
					NK_ASSERT(false, "eDirect������");
					/*for (int i = 0; i < VertexCount_; i++)
					{
					FbxVector2 tex = FBXLayerUV->GetDirectArray().GetAt(i);
					vertex[i].Tex = Vector2(tex[0], 1.0f - tex[1]);
					}*/
				}
			}

			UVSetName_ = FBXLayerUV->GetName();
		}

	}



	void Mesh::CreateSkeletonBuffer(FbxMesh * fbxMesh)
	{
		//���_�o�b�t�@�̍쐬.
		//���_��.
		VertexCount_ = fbxMesh->GetControlPointsCount();
		//���_�o�b�t�@�̃\�[�X�f�[�^�B
		VertexBuffer_SkeletonS* vertexTmp = new VertexBuffer_SkeletonS[VertexCount_];
		vector<VertexBuffer_SkeletonS> VERTEX_TMP_LIST;
		VERTEX_TMP_LIST.resize(VertexCount_);

		Matrix mTmp = Matrix::FbxToMatrix(fbxMesh->GetNode()->EvaluateGlobalTransform());

		//���_�̓ǂݎ��.
		for (int i = 0; i < VertexCount_; i++)
		{
			FbxVector4 FBXVertex = fbxMesh->GetControlPointAt(i);

			Vector3 Pos = Vector3((float)FBXVertex[0], (float)FBXVertex[1], (float)FBXVertex[2]);
			Pos.TransformCoord(mTmp);
			vertexTmp[i].Pos.x = Pos.x;
			vertexTmp[i].Pos.y = Pos.y;
			vertexTmp[i].Pos.z = Pos.z;
			vertexTmp[i].Pos.w = 1.0f;
			VERTEX_TMP_LIST[i].Pos = Vector4(Pos.x, Pos.y, Pos.z, 1.0f);
		}

		//�C���f�b�N�X�o�b�t�@�̍쐬.
		int indexCount = 0;

		int polygonCount = fbxMesh->GetPolygonCount();

		for (int i = 0; i < polygonCount; i++)
		{
			int polygonSize = fbxMesh->GetPolygonSize(i);

			switch (polygonSize)
			{
			case 3:
				indexCount += 3;
				break;
			case 4:
				indexCount += 6;
				break;
			default:
				break;
			}
		}

		USHORT* index = new USHORT[indexCount];
		vector<USHORT> INDEXLIST;
		INDEXLIST.resize(indexCount);

		UINT Index = 0;
		for (int i = 0; i < polygonCount; i++)
		{
			// 1�|���S�����̒��_�����擾
			int lPolygonSize = fbxMesh->GetPolygonSize(i);

			switch (lPolygonSize)
			{
			case 3:  // �O�p�|���S��
				for (int j = 0; j < 3; j++)
				{
					// �R���g���[���|�C���g�̃C���f�b�N�X���擾
					index[Index] = fbxMesh->GetPolygonVertex(i, j);
					INDEXLIST[Index] = fbxMesh->GetPolygonVertex(i, j);
					Index++;
				}
				break;
			case 4: // �l�p�|���S��
				for (int j = 0; j < 6; j++)
				{
					// �R���g���[���|�C���g�̃C���f�b�N�X���擾
					index[Index] = fbxMesh->GetPolygonVertex(i, IndexArray[j]);
					INDEXLIST[Index] = fbxMesh->GetPolygonVertex(i, IndexArray[j]);
					Index++;
				}
				break;
			}
		}

		for (int i = 0; i < indexCount;)
		{
			Vector3 Pos_0 = Vector3(vertexTmp[index[i]].Pos.x, vertexTmp[index[i]].Pos.y, vertexTmp[index[i]].Pos.z);
			Vector3 Pos_1 = Vector3(vertexTmp[index[i + 1]].Pos.x, vertexTmp[index[i + 1]].Pos.y, vertexTmp[index[i + 1]].Pos.z);
			Vector3 Pos_2 = Vector3(vertexTmp[index[i + 2]].Pos.x, vertexTmp[index[i + 2]].Pos.y, vertexTmp[index[i + 2]].Pos.z);

			Vector3 Pos0To1, Pos0To2;
			Pos0To1.Sub(Pos_1, Pos_0);
			Pos0To2.Sub(Pos_2, Pos_0);

			Vector3 Normal;
			Normal.Cross(Pos0To1, Pos0To2);

			vertexTmp[index[i]].Normal.Add(Normal);
			vertexTmp[index[i + 1]].Normal.Add(Normal);
			vertexTmp[index[i + 2]].Normal.Add(Normal);

			VERTEX_TMP_LIST[index[i]].Normal.Add(Normal);
			VERTEX_TMP_LIST[index[i + 1]].Normal.Add(Normal);
			VERTEX_TMP_LIST[index[i + 2]].Normal.Add(Normal);

			i += 3;
		}

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
		int BoneCount = 0;

		if (FBXSkin != nullptr)
		{
			//�{�[����.
			int boneCount = FBXSkin->GetClusterCount();
			for (int i = 0; i < boneCount; i++)
			{
				FbxCluster* FBXBone = FBXSkin->GetCluster(i);

				switch (FBXBone->GetLinkMode())
				{
				case FbxCluster::eNormalize:
					/**
					* �E�F�C�g�̍��v��1.0�ɂȂ��Ă���Ă�.
					*/
				{
					//���̃{�[���ɂ���Ĉړ����钸�_�̐�.
					int boneIndexCount = FBXBone->GetControlPointIndicesCount();

					int* boneIndex = FBXBone->GetControlPointIndices();

					double* boneWeight = FBXBone->GetControlPointWeights();

					for (int j = 0; j < boneIndexCount; j++)
					{
						VertexBoneList[boneIndex[j]].BoneIndex_.push_back(BoneCount);
						VertexBoneList[boneIndex[j]].BoneWeight_.push_back(boneWeight[j]);
					}
				}
				break;
				case FbxCluster::eAdditive:
				{
					NK_ASSERT(false, "eAdditive������.");
				}
				break;
				case FbxCluster::eTotalOne:
				{
					NK_ASSERT(false, "eTotalOne������.");
				}
				break;
				}

				BoneCount++;
			}
		}


		//���_��.
		VertexCount_ = indexCount;
		//���_�o�b�t�@�̃\�[�X�f�[�^�B
		VertexBuffer_SkeletonS* vertex = new VertexBuffer_SkeletonS[VertexCount_];

		for (int i = 0; i < indexCount; i++)
		{
			vertex[i].Pos = vertexTmp[index[i]].Pos;
			vertex[i].Normal = vertexTmp[index[i]].Normal;
			for (int bone = 0; bone < 4; bone++)
			{
				vertex[i].BoneIndex_[bone] = vertexTmp[index[i]].BoneIndex_[bone];
				vertex[i].BoneWeight_[bone] = vertexTmp[index[i]].BoneWeight_[bone];
			}
		}

		delete[] vertexTmp;
		vertexTmp = nullptr;

		//UV���W��ݒ�.
		FbxLayerElementUV* FBXLayerUV = fbxMesh->GetLayer(0)->GetUVs();

		if (FBXLayerUV)
		{
			if (FBXLayerUV->GetMappingMode() == FbxLayerElement::eByPolygonVertex)
			{
				if (FBXLayerUV->GetReferenceMode() == FbxLayerElement::eIndexToDirect)
				{
					int uvIndex = 0;
					int offset = 0;
					for (int i = 0; i < polygonCount; i++)
					{
						// 1�|���S�����̒��_�����擾
						int lPolygonSize = fbxMesh->GetPolygonSize(i);
						switch (lPolygonSize)
						{
						case 3:
						{
							for (int j = 0; j < 3; j++)
							{
								int index = FBXLayerUV->GetIndexArray().GetAt(j + offset);
								FbxVector2 FBXTex = FBXLayerUV->GetDirectArray().GetAt(index);
								vertex[uvIndex].Tex = Vector2(FBXTex[0], 1.0f - FBXTex[1]);
								uvIndex++;
							}
						}
						break;
						case 4:
						{
							for (int j = 0; j < 6; j++)
							{
								int index = FBXLayerUV->GetIndexArray().GetAt(IndexArray[j] + offset);
								FbxVector2 FBXTex = FBXLayerUV->GetDirectArray().GetAt(index);
								vertex[uvIndex].Tex = Vector2(FBXTex[0], 1.0f - FBXTex[1]);
								uvIndex++;
							}
						}
						break;
						}
						offset += lPolygonSize;
					}
				}
			}
			else if (FBXLayerUV->GetMappingMode() == FbxLayerElement::eByControlPoint)
			{
				if (FBXLayerUV->GetReferenceMode() == FbxLayerElement::eDirect)
				{
					NK_ASSERT(false, "eDirect������");
					/*for (int i = 0; i < VertexCount_; i++)
					{
					FbxVector2 tex = FBXLayerUV->GetDirectArray().GetAt(i);
					vertex[i].Tex = Vector2(tex[0], 1.0f - tex[1]);
					}*/
				}
			}

			UVSetName_ = FBXLayerUV->GetName();
		}


		//�ڃx�N�g�������߂�.
		for (int i = 0; i < VertexCount_;)
		{
			Vector3 CP0[3] =
			{
				Vector3(vertex[i].Pos.x, vertex[i].Tex.x, vertex[i].Tex.y),
				Vector3(vertex[i].Pos.y, vertex[i].Tex.x, vertex[i].Tex.y),
				Vector3(vertex[i].Pos.z, vertex[i].Tex.x, vertex[i].Tex.y),
			};
			Vector3 CP1[3] =
			{
				Vector3(vertex[i + 1].Pos.x, vertex[i + 1].Tex.x, vertex[i + 1].Tex.y),
				Vector3(vertex[i + 1].Pos.y, vertex[i + 1].Tex.x, vertex[i + 1].Tex.y),
				Vector3(vertex[i + 1].Pos.z, vertex[i + 1].Tex.x, vertex[i + 1].Tex.y),
			};
			Vector3 CP2[3] =
			{
				Vector3(vertex[i + 2].Pos.x, vertex[i + 2].Tex.x, vertex[i + 2].Tex.y),
				Vector3(vertex[i + 2].Pos.y, vertex[i + 2].Tex.x, vertex[i + 2].Tex.y),
				Vector3(vertex[i + 2].Pos.z, vertex[i + 2].Tex.x, vertex[i + 2].Tex.y),
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

			vertex[i].Tangent = Vector3(U[0], U[1], U[2]);
			vertex[i + 1].Tangent = Vector3(U[0], U[1], U[2]);
			vertex[i + 2].Tangent = Vector3(U[0], U[1], U[2]);

			i += 3;
		}


		//���_�o�b�t�@.
		VertexBuffer_.Create(vertex, VertexCount_, sizeof(VertexBufferS));
	}

	/**
	* �}�e���A���̍쐬.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	*/
	void Mesh::CreateMaterial(FbxNode * fbxNode, ModelData* modelData)
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
							if (UVSetName_ == uvSetName)
							{
								bool isTexture = false;
								int materialNum = 0;
								for (auto& it : modelData->GetMaterialList())
								{
									if (it->TextureName_ == textureName)
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
						if (UVSetName_ == uvSetName)
						{
							bool isTexture = false;
							int materialNum = 0;
							for (auto& it : modelData->GetMaterialList())
							{
								if (it->TextureName_ == textureName)
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