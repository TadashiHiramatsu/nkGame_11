/**
* ���b�V���N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* ���b�V���N���X.
	*/
	class Mesh : Noncopyable
	{
	public:

		/**
		* ���_�o�b�t�@�\����.
		*/
		struct VertexBufferS
		{
			Vector4 Pos = Vector4(0, 0, 0, 1);	//!< ���_.
			Vector3 Normal = Vector3::Zero;			//!< �@��.
		};

	public:

		/**
		* �ǂݍ���.
		*
		* @param fbxMesh	FBXSDK�̃��b�V���N���X.
		* @param parent		�e�̃g�����X�t�H�[���|�C���^.
		*/
		void Load(FbxMesh* fbxMesh,Transform* parent);

		/**
		* �X�V.
		*/
		void Update();

		/**
		* �`��.
		*/
		void Render();

		/**
		* ���[���h�s����擾.
		*/
		const Matrix& GetWorldMatrix()
		{
			return LocalTransform_.WorldMatrix_;
		}

		/**
		* �C���f�b�N�X�����擾.
		*/
		UINT GetIndexCount()
		{
			return IndexCount_;
		}

		/**
		* �g�����X�t�H�[���̃|�C���^���擾.
		*/
		Transform* GetTransform()
		{
			return &LocalTransform_;
		}

	private:
		 
		/**
		* �o�b�t�@�̍쐬.
		*
		* @param fbxMesh	FBXSDK�̃��b�V���N���X.
		*/
		void CreateBuffer(FbxMesh* fbxMesh);

	private:

		/** ���b�V����. */
		string Name_ = "NonName";

		/** ���[�J���g�����X�t�H�[��. */
		Transform LocalTransform_;

		/** ���_�o�b�t�@. */
		VertexBuffer VertexBuffer_;
		/** ���_��. */
		UINT VertexCount_ = 0;
		/** �C���f�b�N�X�o�b�t�@. */
		IndexBuffer IndexBuffer_;
		/** �C���f�b�N�X��. */
		UINT IndexCount_ = 0;

	};
}