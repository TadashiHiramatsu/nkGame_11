/**
* メッシュクラスの実装.
*/
#include"nkstdafx.h"
#include"nkMesh.h"

namespace nkEngine
{

	namespace
	{

		//四角ポリゴンを三角ポリゴンに変換する値.
		static const UINT IndexArray[6] = { 0, 1, 2, 0, 2, 3 };

		/**
		* テクスチャ名を特定.
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
	* 読み込み.
	*
	* @param fbxMesh	FBXSDKのメッシュクラス.
	* @param parent		親のトランスフォームポインタ.
	*/
	void Mesh::Load(FbxMesh * fbxMesh, Transform* parent, ModelData* modelData)
	{
		//名前を取得.
		Name_ = fbxMesh->GetNode()->GetName();
		
		//親のトランスフォームを設定.
		LocalTransform_.Parent_ = parent;

		//バッファの作成.
		CreateBuffer(fbxMesh);

		//マテリアルの作成.
		CreateMaterial(fbxMesh->GetNode(), modelData);
	
	}

	/**
	* 更新.
	*/
	void Mesh::Update()
	{
		//トランスフォームの更新.
		LocalTransform_.Update();
	}

	/**
	* 描画.
	*/
	void Mesh::Render()
	{
		//頂点バッファを設定.
		Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);
		//プリミティブのトポロジーを設定.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//描画。
		Engine().GetRenderContext().Draw(VertexCount_, 0);
	}

	/**
	* バッファの作成.
	*
	* @param fbxMesh	FBXSDKのメッシュクラス.
	*/
	void Mesh::CreateBuffer(FbxMesh * fbxMesh)
	{
	
		//頂点数.
		VertexCount_ = fbxMesh->GetControlPointsCount();

		//頂点バッファのソースデータ.
		vector<VertexBufferS> vertexTmpList;
		vertexTmpList.resize(VertexCount_);

		//頂点座標を読み込み.
		LoadPosition(vertexTmpList, fbxMesh);

		//インデックスリスト.
		vector<USHORT> indexList;

		//インデックスリストを作成.
		CreateIndexList(indexList, fbxMesh);

		//法線を計算.
		CreateNormal(vertexTmpList, indexList);

		//頂点数.
		VertexCount_ = indexList.size();
		//頂点バッファのソースデータ.
		vector<VertexBufferS> vertexList;
		vertexList.resize(VertexCount_);

		for (int i = 0; i < indexList.size(); i++)
		{
			vertexList[i].Pos = vertexTmpList[indexList[i]].Pos;
			vertexList[i].Normal = vertexTmpList[indexList[i]].Normal;
		}

		vertexTmpList.clear();

		//UV座標を読み込み.
		LoadUV(vertexList, fbxMesh);

		//接ベクトルを計算.
		CreateTanget(vertexList);

		//頂点バッファ.
		VertexBuffer_.Create(vertexList.data(), VertexCount_, sizeof(VertexBufferS));

	}

	/**
	* 頂点座標を読み込む.
	*
	* @param vertexList	頂点リスト.
	* @param fbxMesh	FBXSDKのメッシュクラス.
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
	* インデックスリストを作成する.
	*
	* @param indexList	インデックスリスト.
	* @param fbxMesh	FBXSDKのメッシュクラス.
	*/
	void Mesh::CreateIndexList(vector<USHORT>& indexList, FbxMesh * fbxMesh)
	{
		//インデックスバッファの作成.
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
			// 1ポリゴン内の頂点数を取得
			int lPolygonSize = fbxMesh->GetPolygonSize(i);

			switch (lPolygonSize)
			{
			case 3:  // 三角ポリゴン
				for (int j = 0; j < 3; j++)
				{
					// コントロールポイントのインデックスを取得
					indexList[Index] = fbxMesh->GetPolygonVertex(i, j);
					Index++;
				}
				break;
			case 4: // 四角ポリゴン
				for (int j = 0; j < 6; j++)
				{
					// コントロールポイントのインデックスを取得
					indexList[Index] = fbxMesh->GetPolygonVertex(i, IndexArray[j]);
					Index++;
				}
				break;
			}
		}

	}

	/**
	* 法線を作成.
	*
	* @param vertexList	頂点リスト.
	* @param indexList	インデックスリスト.
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
	* 接ベクトルを作成.
	*
	* @param vertexList	頂点リスト.
	*/
	void Mesh::CreateTanget(vector<VertexBufferS>& vertexList)
	{
		//接ベクトルを求める.
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

			//接ベクトル.
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
	* UV座標を読み込み.
	*/
	void Mesh::LoadUV(vector<VertexBufferS>& vertexList, FbxMesh * fbxMesh)
	{
		int polygonCount = fbxMesh->GetPolygonCount();

		//UV座標を設定.
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
						// 1ポリゴン内の頂点数を取得
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
					NK_ASSERT(false, "eDirect未実装");
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
		//頂点バッファの作成.
		//頂点数.
		VertexCount_ = fbxMesh->GetControlPointsCount();
		//頂点バッファのソースデータ。
		VertexBuffer_SkeletonS* vertexTmp = new VertexBuffer_SkeletonS[VertexCount_];
		vector<VertexBuffer_SkeletonS> VERTEX_TMP_LIST;
		VERTEX_TMP_LIST.resize(VertexCount_);

		Matrix mTmp = Matrix::FbxToMatrix(fbxMesh->GetNode()->EvaluateGlobalTransform());

		//頂点の読み取り.
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

		//インデックスバッファの作成.
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
			// 1ポリゴン内の頂点数を取得
			int lPolygonSize = fbxMesh->GetPolygonSize(i);

			switch (lPolygonSize)
			{
			case 3:  // 三角ポリゴン
				for (int j = 0; j < 3; j++)
				{
					// コントロールポイントのインデックスを取得
					index[Index] = fbxMesh->GetPolygonVertex(i, j);
					INDEXLIST[Index] = fbxMesh->GetPolygonVertex(i, j);
					Index++;
				}
				break;
			case 4: // 四角ポリゴン
				for (int j = 0; j < 6; j++)
				{
					// コントロールポイントのインデックスを取得
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
				//FBXスキンクラスにダウンキャスト.
				FBXSkin = (FbxSkin*)FBXDeformer;
			}
		}

		vector<VertexBoneS> VertexBoneList;
		VertexBoneList.resize(VertexCount_);
		int BoneCount = 0;

		if (FBXSkin != nullptr)
		{
			//ボーン数.
			int boneCount = FBXSkin->GetClusterCount();
			for (int i = 0; i < boneCount; i++)
			{
				FbxCluster* FBXBone = FBXSkin->GetCluster(i);

				switch (FBXBone->GetLinkMode())
				{
				case FbxCluster::eNormalize:
					/**
					* ウェイトの合計が1.0になってるってよ.
					*/
				{
					//このボーンによって移動する頂点の数.
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
					NK_ASSERT(false, "eAdditive未実装.");
				}
				break;
				case FbxCluster::eTotalOne:
				{
					NK_ASSERT(false, "eTotalOne未実装.");
				}
				break;
				}

				BoneCount++;
			}
		}


		//頂点数.
		VertexCount_ = indexCount;
		//頂点バッファのソースデータ。
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

		//UV座標を設定.
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
						// 1ポリゴン内の頂点数を取得
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
					NK_ASSERT(false, "eDirect未実装");
					/*for (int i = 0; i < VertexCount_; i++)
					{
					FbxVector2 tex = FBXLayerUV->GetDirectArray().GetAt(i);
					vertex[i].Tex = Vector2(tex[0], 1.0f - tex[1]);
					}*/
				}
			}

			UVSetName_ = FBXLayerUV->GetName();
		}


		//接ベクトルを求める.
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

			//接ベクトル.
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


		//頂点バッファ.
		VertexBuffer_.Create(vertex, VertexCount_, sizeof(VertexBufferS));
	}

	/**
	* マテリアルの作成.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	*/
	void Mesh::CreateMaterial(FbxNode * fbxNode, ModelData* modelData)
	{
		
		//マテリアル数.
		int materialCount = fbxNode->GetMaterialCount();

		if (materialCount > 0)
		{
			FbxSurfaceMaterial* FBXMaterial = fbxNode->GetMaterial(0);

			FbxProperty prop = FBXMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);
			
			//FbxLayeredTextureの数.
			int LayeredTextureCount = prop.GetSrcObjectCount<FbxLayeredTexture>();

			if (LayeredTextureCount > 0)
			{
				//--- アタッチされたテクスチャの数だけ繰り返す ---//
				for (int j = 0; LayeredTextureCount > j; j++) {

					//--- テクスチャを取得 ---//
					FbxLayeredTexture* layeredTexture = prop.GetSrcObject<FbxLayeredTexture>(j);
					//--- レイヤー数を取得 ---//
					int textureCount = layeredTexture->GetSrcObjectCount<FbxFileTexture>();

					//--- レイヤー数だけ繰り返す ---//
					for (int k = 0; textureCount > k; k++) {
						//--- テクスチャを取得 ---//
						FbxFileTexture* texture = prop.GetSrcObject<FbxFileTexture>(k);

						if (texture) 
						{
							//テクスチャ名を取得.
							std::string textureName = texture->GetRelativeFileName();

							textureName = TextureNameSearch(textureName);

							//--- UVSet名を取得 ---//
							std::string uvSetName = texture->UVSet.Get().Buffer();

							//--- UVSet名を比較し対応しているテクスチャなら保持 ---//
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
				//テクスチャ数を取得.
				int fileTextureCount = prop.GetSrcObjectCount<FbxFileTexture>();

				if (0 < fileTextureCount)
				{
					FbxFileTexture* FBXTexture = prop.GetSrcObject<FbxFileTexture>(0);
					
					if (FBXTexture) 
					{
						//テクスチャ名を取得.
						std::string textureName = FBXTexture->GetRelativeFileName();

						textureName = TextureNameSearch(textureName);

						//--- UVSet名を取得 ---//
						std::string uvSetName = FBXTexture->UVSet.Get().Buffer();

						//--- UVSet名を比較し対応しているテクスチャなら保持 ---//
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