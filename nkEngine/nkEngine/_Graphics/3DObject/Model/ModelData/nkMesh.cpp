/**
* ���b�V���N���X�̎���.
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
	* �ǂݍ���.
	*
	* @param fbxMesh	FBXSDK�̃��b�V���N���X.
	* @param parent		�e�̃g�����X�t�H�[���|�C���^.
	*/
	void Mesh::Load(FbxMesh * fbxMesh, Transform* parent)
	{

		//�o�b�t�@�̍쐬.
		CreateBuffer(fbxMesh);

		//�e�̃g�����X�t�H�[����ݒ�.
		LocalTransform_.Parent_ = parent;

		Name_ = fbxMesh->GetName();

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
		//�C���f�b�N�X�o�b�t�@��ݒ�.
		Engine().GetRenderContext().IASetIndexBuffer(IndexBuffer_, DXGI_FORMAT_R16_UINT);
		//�v���~�e�B�u�̃g�|���W�[��ݒ�.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�`��B
		Engine().GetRenderContext().DrawIndexed(IndexCount_, 0, 0);
	}

	/**
	* �o�b�t�@�̍쐬.
	*
	* @param fbxMesh	FBXSDK�̃��b�V���N���X.
	*/
	void Mesh::CreateBuffer(FbxMesh * fbxMesh)
	{
		//���_�o�b�t�@�̍쐬.
		//���_��.
		VertexCount_ = fbxMesh->GetControlPointsCount();
		//���_�o�b�t�@�̃\�[�X�f�[�^�B
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

		//�C���f�b�N�X�o�b�t�@�̍쐬.
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
			// 1�|���S�����̒��_�����擾
			int lPolygonSize = fbxMesh->GetPolygonSize(i);

			switch (lPolygonSize)
			{
			case 3:  // �O�p�|���S��
				for (int j = 0; j < 3; j++)
				{
					// �R���g���[���|�C���g�̃C���f�b�N�X���擾
					index[Index] = fbxMesh->GetPolygonVertex(i, j);
					Index++;
				}
				break;
			case 4: // �l�p�|���S��
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

		//���_�o�b�t�@.
		VertexBuffer_.Create(vertex, VertexCount_, sizeof(VertexBufferS));
		//�C���f�b�N�X�o�b�t�@���쐬.
		IndexBuffer_.Create(index, IndexCount_);
	}

}