/**
* ���b�V���m�[�h�N���X�̒�`.
*/
#pragma once

#include"nkNode.h"

namespace nkEngine
{

	class Material;

	/**
	* ���b�V���m�[�h�N���X.
	*/
	class MeshNode : public INode
	{
	public:

		/**
		* ���_�o�b�t�@�\����.
		*/
		struct VertexBufferS
		{
			Vector4 Pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);	//!< ���_���W.
			Vector2 Tex = Vector2::Zero;		//!< UV���W.
			Vector3 Normal = Vector3::Zero;		//!< �@���x�N�g��.
			Vector3 Tangent = Vector3::Zero;	//!< �ڃx�N�g��
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		MeshNode()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~MeshNode()
		{
		}

		/**
		* �쐬.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X.
		* @param parent		�e�̃|�C���^.
		* @param modelData	���f���f�[�^.
		*/
		void Create(FbxNode* fbxNode,Transform* parent, ModelData* modelData)override;

		/**
		* �`��.
		*/
		void Render()override;

		/**
		* ���[���h�s����擾.
		*/
		const Matrix& GetWorldMatrix()
		{
			return Transform_.WorldMatrix_;
		}

		/**
		* �Ή������}�e���A���ԍ����擾.
		*/
		int GetMaterialNum() const
		{
			return MaterialNum_;
		}

		/**
		* ���_���W���X�g���擾.
		*/
		vector<Vector3>& GetVertexPosList()
		{
			return VertexPosList_;
		}
		
	private:

		/**
		* ���_�o�b�t�@�̍쐬.
		*/
		void CreateVertexBuffer(FbxMesh* fbxMesh);

		/**
		* �ڃx�N�g�����쐬.
		*
		* @param vertexList	���_���X�g.
		*/
		void CreateTanget(vector<VertexBufferS>& vertexList);

		/**
		* �}�e���A���̍쐬.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X. 
		*/
		void CreateMaterial(FbxNode* fbxNode,ModelData* modelData);

	private:

		/** ���_���W���X�g. */
		vector<Vector3> VertexPosList_;
		/** ���_�o�b�t�@. */
		VertexBuffer VertexBuffer_;
		/** ���_��. */
		UINT VertexCount_ = 0;

		/** �Ή�����}�e���A���ԍ�. */
		int MaterialNum_ = -1;

		/** UV�Z�b�g��. */
		vector<string> UVSetNameList_;

	};

}