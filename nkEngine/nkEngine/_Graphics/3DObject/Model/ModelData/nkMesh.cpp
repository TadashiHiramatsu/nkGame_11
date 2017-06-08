/**
* メッシュクラスの実装.
*/
#include"nkstdafx.h"
#include"nkMesh.h"

namespace
{
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

namespace nkEngine
{

	/**
	* 読み込み.
	*
	* @param fbxMesh	FBXSDKのメッシュクラス.
	* @param parent		親のトランスフォームポインタ.
	*/
	void Mesh::Load(FbxMesh * fbxMesh, Transform* parent, ModelData* modelData)
	{

		//バッファの作成.
		CreateBuffer(fbxMesh);

		//マテリアルの作成.
		CreateMaterial(fbxMesh->GetNode(), modelData);

		//親のトランスフォームを設定.
		LocalTransform_.Parent_ = parent;

		//名前を取得.
		Name_ = fbxMesh->GetNode()->GetName();

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
		//頂点バッファの作成.
		//頂点数.
		VertexCount_ = fbxMesh->GetControlPointsCount();
		//頂点バッファのソースデータ。
		VertexBufferS* vertexTmp = new VertexBufferS[VertexCount_];

		Matrix mTmp = Matrix::FbxToMatrix(fbxMesh->GetNode()->EvaluateGlobalTransform());

		for (int i = 0; i < VertexCount_; i++)
		{
			FbxVector4 FBXVertex = fbxMesh->GetControlPointAt(i);

			Vector3 Pos = Vector3((float)FBXVertex[0], (float)FBXVertex[1], (float)FBXVertex[2]);
			Pos.TransformCoord(mTmp);
			vertexTmp[i].Pos.x = Pos.x;
			vertexTmp[i].Pos.y = Pos.y;
			vertexTmp[i].Pos.z = Pos.z;
			vertexTmp[i].Pos.w = 1.0f;
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
					Index++;
				}
				break;
			case 4: // 四角ポリゴン
				for (int j = 0; j < 6; j++)
				{
					// コントロールポイントのインデックスを取得
					index[Index] = fbxMesh->GetPolygonVertex(i, IndexArray[j]);
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

			i += 3;
		}

		//頂点数.
		VertexCount_ = indexCount;
		//頂点バッファのソースデータ。
		VertexBufferS* vertex = new VertexBufferS[VertexCount_];

		for (int i = 0; i < indexCount; i++)
		{
			vertex[i].Pos = vertexTmp[index[i]].Pos;
			vertex[i].Normal = vertexTmp[index[i]].Normal;
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
				Vector3(vertex[i].Pos.x,vertex[i].Tex.x,vertex[i].Tex.y),
				Vector3(vertex[i].Pos.y,vertex[i].Tex.x,vertex[i].Tex.y),
				Vector3(vertex[i].Pos.z,vertex[i].Tex.x,vertex[i].Tex.y),
			};
			Vector3 CP1[3] =
			{
				Vector3(vertex[i + 1].Pos.x,vertex[i + 1].Tex.x,vertex[i + 1].Tex.y),
				Vector3(vertex[i + 1].Pos.y,vertex[i + 1].Tex.x,vertex[i + 1].Tex.y),
				Vector3(vertex[i + 1].Pos.z,vertex[i + 1].Tex.x,vertex[i + 1].Tex.y),
			};
			Vector3 CP2[3] =
			{
				Vector3(vertex[i + 2].Pos.x,vertex[i + 2].Tex.x,vertex[i + 2].Tex.y),
				Vector3(vertex[i + 2].Pos.y,vertex[i + 2].Tex.x,vertex[i + 2].Tex.y),
				Vector3(vertex[i + 2].Pos.z,vertex[i + 2].Tex.x,vertex[i + 2].Tex.y),
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