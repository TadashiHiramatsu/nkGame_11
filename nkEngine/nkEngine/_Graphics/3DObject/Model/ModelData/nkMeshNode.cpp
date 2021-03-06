/**
* メッシュノードクラスの実装.
*/
#include"nkstdafx.h"
#include"nkMeshNode.h"

#include<fbxsdk.h>

namespace nkEngine
{

	namespace
	{

		//四角ポリゴンを三角ポリゴンに変換する値.
		static const UINT IndexArray4[6] = { 3, 2, 0, 2, 1, 0 };
		static const UINT IndexArray3[3] = { 2, 1, 0 };

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
	* 作成.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	* @param parent		親のポインタ.
	* @param modelData	モデルデータ.
	*/
	void MeshNode::Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)
	{
		//メッシュタイプに設定.
		NodeType_ = NodeTypeE::Mesh;

		//頂点バッファを作成.
		CreateVertexBuffer(fbxNode->GetMesh());

		//マテリアルの作成.
		CreateMaterial(fbxNode, modelData);
		
		INode::Create(fbxNode, parent, modelData);
	}

	/**
	* 描画.
	*/
	void MeshNode::Render()
	{
		//頂点バッファを設定.
		Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);
		//プリミティブのトポロジーを設定.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 
		//Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		//描画。
		Engine().GetRenderContext().Draw(VertexCount_, 0);
	}

	/**
	* 頂点バッファの作成.
	*/
	void MeshNode::CreateVertexBuffer(FbxMesh * fbxMesh)
	{
		//頂点バッファのソースデータ.
		vector<VertexBufferS> vertexList;

		//頂点座標リスト.
		FbxVector4* pVertex = fbxMesh->GetControlPoints();

		Matrix mTmp = Matrix::FbxToMatrix(fbxMesh->GetNode()->EvaluateGlobalTransform());

		FbxStringList lUVSetNameList;
		fbxMesh->GetUVSetNames(lUVSetNameList);
		for (int i = 0; i < lUVSetNameList.GetCount(); i++)
		{
			FbxString name = lUVSetNameList[i];
			UVSetNameList_.push_back(name.Buffer());
		}

		//ポリゴン数繰り返す.
		for (int i = 0; i < fbxMesh->GetPolygonCount(); i++)
		{
			//ポリゴンサイズ.
			int numVertex = fbxMesh->GetPolygonSize(i);

			switch (numVertex)
			{
				case 3:
				{
					for (int j = 0; j < 3; j++)
					{
						//頂点.
						VertexBufferS vertex;

						//頂点座標インデックス.
						int cpIndex = fbxMesh->GetPolygonVertex(i, IndexArray3[j]);
						Vector3 pos = Vector3(-pVertex[cpIndex].mData[0], pVertex[cpIndex].mData[1], pVertex[cpIndex].mData[2]);
						pos.TransformCoord(mTmp);
						//頂点座標を設定.
						vertex.Pos.Set(pos);
						VertexPosList_.push_back(pos);

						//法線.
						FbxVector4 FBXnormal;
						fbxMesh->GetPolygonVertexNormal(i, IndexArray3[j], FBXnormal);
						Vector3 normal = Vector3(-FBXnormal.mData[0], FBXnormal.mData[1], FBXnormal.mData[2]);
						normal.TransformCoord(mTmp);
						//法線を設定.
						vertex.Normal = normal;

						//UV設定
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
						//頂点.
						VertexBufferS vertex;

						//頂点座標インデックス.
						int cpIndex = fbxMesh->GetPolygonVertex(i, IndexArray4[j]);
						Vector3 pos = Vector3(-pVertex[cpIndex].mData[0], pVertex[cpIndex].mData[1], pVertex[cpIndex].mData[2]);
						pos.TransformCoord(mTmp);
						//頂点座標を設定.
						vertex.Pos.Set(pos);
						VertexPosList_.push_back(pos);

						//法線.
						FbxVector4 FBXnormal;
						fbxMesh->GetPolygonVertexNormal(i, IndexArray4[j], FBXnormal);
						Vector3 normal = Vector3(-FBXnormal.mData[0], FBXnormal.mData[1], FBXnormal.mData[2]);
						normal.TransformCoord(mTmp);
						//法線を設定.
						vertex.Normal = normal;

						//UV設定
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

		//頂点数を取得.
		VertexCount_ = vertexList.size();

		//接ベクトルを計算.
		CreateTanget(vertexList);

		//頂点バッファ.
		VertexBuffer_.Create(vertexList.data(), VertexCount_, sizeof(VertexBufferS));

	}

	/**
	* 接ベクトルを作成.
	*
	* @param vertexList	頂点リスト.
	*/
	void MeshNode::CreateTanget(vector<VertexBufferS>& vertexList)
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
	* マテリアルの作成.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	*/
	void MeshNode::CreateMaterial(FbxNode * fbxNode, ModelData* modelData)
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