/**
* メッシュクラスの実装.
*/
#include"nkstdafx.h"
#include"nkMesh.h"

namespace
{
	static const UINT IndexArray[6] = { 0, 1, 2, 0, 2, 3 };
}

namespace nkEngine
{

	/**
	* 読み込み.
	*
	* @param fbxMesh	FBXSDKのメッシュクラス.
	* @param parent		親のトランスフォームポインタ.
	*/
	void Mesh::Load(FbxMesh * fbxMesh, Transform* parent)
	{

		//バッファの作成.
		CreateBuffer(fbxMesh);

		//親のトランスフォームを設定.
		LocalTransform_.Parent_ = parent;

		Name_ = fbxMesh->GetName();

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
		//インデックスバッファを設定.
		Engine().GetRenderContext().IASetIndexBuffer(IndexBuffer_, DXGI_FORMAT_R16_UINT);
		//プリミティブのトポロジーを設定.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//描画。
		Engine().GetRenderContext().DrawIndexed(IndexCount_, 0, 0);
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
		VertexBufferS* vertex = new VertexBufferS[VertexCount_];

		FbxVector4* FBXVertex = fbxMesh->GetControlPoints();

		Matrix mTmp = Matrix::FbxToMatrix(fbxMesh->GetNode()->EvaluateGlobalTransform());

		for (int i = 0; i < VertexCount_; i++)
		{
			Vector3 Pos = Vector3((float)FBXVertex[i][0], (float)FBXVertex[i][1], (float)FBXVertex[i][2]);
			Pos.TransformCoord(mTmp);
			vertex[i].Pos.x = Pos.x;
			vertex[i].Pos.y = Pos.y;
			vertex[i].Pos.z = Pos.z;
			vertex[i].Pos.w = 1.0f;
		}

		//インデックスバッファの作成.
		IndexCount_ = 0;

		int polygonCount = fbxMesh->GetPolygonCount();

		for (int i = 0; i < polygonCount; i++)
		{
			int polygonSize = fbxMesh->GetPolygonSize(i);

			switch (polygonSize)
			{
			case 3:
				IndexCount_ += 3;
				break;
			case 4:
				IndexCount_ += 6;
				break;
			default:
				break;
			}
		}

		USHORT* index = new USHORT[IndexCount_];

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
					index[Index] = fbxMesh->GetPolygonVertex(i, IndexArray[j]);
					Index++;
				}
				break;
			}
		}

		for (int i = 0; i < IndexCount_;)
		{
			Vector3 Pos_0 = Vector3(vertex[index[i]].Pos.x, vertex[index[i]].Pos.y, vertex[index[i]].Pos.z);
			Vector3 Pos_1 = Vector3(vertex[index[i + 1]].Pos.x, vertex[index[i + 1]].Pos.y, vertex[index[i + 1]].Pos.z);
			Vector3 Pos_2 = Vector3(vertex[index[i + 2]].Pos.x, vertex[index[i + 2]].Pos.y, vertex[index[i + 2]].Pos.z);

			Vector3 Pos0To1, Pos0To2;
			Pos0To1.Sub(Pos_1, Pos_0);
			Pos0To2.Sub(Pos_2, Pos_0);

			Vector3 Normal;
			Normal.Cross(Pos0To1, Pos0To2);

			vertex[index[i]].Normal.Add(Normal);
			vertex[index[i + 1]].Normal.Add(Normal);
			vertex[index[i + 2]].Normal.Add(Normal);

			i += 3;
		}

		//頂点バッファ.
		VertexBuffer_.Create(vertex, VertexCount_, sizeof(VertexBufferS));
		//インデックスバッファを作成.
		IndexBuffer_.Create(index, IndexCount_);
	}

}