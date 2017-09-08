/**
 * メッシュコライダークラスの実績.
 */
#include"nkstdafx.h"
#include"nkMeshCollider.h"

#include"_Graphics\3DObject\Model\ModelData\nkMeshNode.h"
#include"_Graphics\3DObject\Model\ModelData\nkSkinMeshNode.h"

namespace nkEngine
{

	/**
	* ModelDataからMeshコライダーを生成.
	*
	* @param model			スキンモデル.
	* @param offsetMatrix	オフセット行列.
	*/
	void MeshCollider::Create(ModelData* model, const Matrix* offsetMatrix)
	{
		StridingMeshInterface_ = new btTriangleIndexVertexArray;

		for (auto node : model->GetNodeList())
		{
			//頂点バッファ.
			vector<Vector3> vbTmp;
			if (node->GetNodeType() == INode::NodeTypeE::Mesh)
			{
				MeshNode* mesh = (MeshNode*)node;
				vbTmp = mesh->GetVertexPosList();
			}
			else if(node->GetNodeType() == INode::NodeTypeE::SkinMesh)
			{
				SkinMeshNode* mesh = (SkinMeshNode*)node;
				vbTmp = mesh->GetVertexPosList();
			}

			if (vbTmp.size() > 0)
			{
				VertexBufferT vb;
				IndexBufferT ib;
				unsigned int index = 0;
				for (auto& pos : vbTmp)
				{

					Vector3 posTmp = pos;
					if (offsetMatrix)
					{
						posTmp.TransformCoord(*offsetMatrix);
					}
					bool isHit = false;
					for (int i = 0; i < vb.size(); i++)
					{
						if (vb[i].x == posTmp.x && vb[i].y == posTmp.y && vb[i].z == posTmp.z)
						{
							isHit = true;
							ib.push_back(i);
							break;
						}
					}
					if (!isHit)
					{
						vb.push_back(posTmp);
						ib.push_back(index++);
					}
				}

				VertexBufferArray_.push_back(vb);
				IndexBufferArray_.push_back(ib);
			}
		}

		//インデックスメッシュを作成。
		btIndexedMesh indexedMesh;
		VertexBufferT vb = VertexBufferArray_.back();
		IndexBufferT ib = IndexBufferArray_.back();
		indexedMesh.m_numTriangles = ib.size() / 3;
		indexedMesh.m_triangleIndexBase = (unsigned char*)(&ib.front());
		indexedMesh.m_triangleIndexStride = 12;
		indexedMesh.m_numVertices = vb.size();
		indexedMesh.m_vertexBase = (unsigned char*)(&vb.front());
		indexedMesh.m_vertexStride = sizeof(Vector3);

		StridingMeshInterface_->addIndexedMesh(indexedMesh);

		//メッシュ形状の作成
		Shape_ = new btBvhTriangleMeshShape(StridingMeshInterface_, true);
	}

}