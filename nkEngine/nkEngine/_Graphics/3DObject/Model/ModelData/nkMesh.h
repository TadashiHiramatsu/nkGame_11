/**
* ���b�V���N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	class ModelData;
	class Material;

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
			Vector2 Tex = Vector2::Zero;		//!< UV���W.
			Vector3 Normal = Vector3::Zero;		//!< �@���x�N�g��.
			Vector3 Tangent = Vector3::Zero;	//!< �ڃx�N�g��
		};

	public:

		/**
		* �ǂݍ���.
		*
		* @param fbxMesh	FBXSDK�̃��b�V���N���X.
		* @param parent		�e�̃g�����X�t�H�[���|�C���^.
		*/
		void Load(FbxMesh* fbxMesh,Transform* parent, ModelData* modelData);

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
		* �g�����X�t�H�[���̃|�C���^���擾.
		*/
		Transform* GetTransform()
		{
			return &LocalTransform_;
		}

		/**
		* �Ή������}�e���A���ԍ����擾.
		*/
		int GetMaterialNum() const
		{
			return MaterialNum_;
		}

	private:
		 
		/**
		* �o�b�t�@�̍쐬.
		*
		* @param fbxMesh	FBXSDK�̃��b�V���N���X.
		*/
		void CreateBuffer(FbxMesh* fbxMesh);

		/**
		* �}�e���A���̍쐬.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X. 
		*/
		void CreateMaterial(FbxNode* fbxNode,ModelData* modelData);

	private:

		/** ���b�V����. */
		string Name_ = "NonName";

		/** ���[�J���g�����X�t�H�[��. */
		Transform LocalTransform_;

		/** ���_�o�b�t�@. */
		VertexBuffer VertexBuffer_;
		/** ���_��. */
		UINT VertexCount_ = 0;

		/** �Ή�����}�e���A���ԍ�. */
		int MaterialNum_ = -1;

		/** UV�Z�b�g��. */
		string UVSetName_;

	};

}