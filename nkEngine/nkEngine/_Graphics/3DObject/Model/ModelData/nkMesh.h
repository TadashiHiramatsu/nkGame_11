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
			Vector4 Pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);	//!< ���_���W.
			Vector2 Tex = Vector2::Zero;		//!< UV���W.
			Vector3 Normal = Vector3::Zero;		//!< �@���x�N�g��.
			Vector3 Tangent = Vector3::Zero;	//!< �ڃx�N�g��
		};

		//struct VertexBoneS
		//{
		//	vector<UINT> BoneIndex_;
		//	vector<float> BoneWeight_;
		//};

		//static const UINT BONE_MAX_SIZE = 4U;
		//struct VertexBuffer_SkeletonS
		//{
		//	Vector4 Pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);	//!< ���_���W.
		//	Vector2 Tex = Vector2::Zero;		//!< UV���W.
		//	Vector3 Normal = Vector3::Zero;		//!< �@���x�N�g��.
		//	Vector3 Tangent = Vector3::Zero;	//!< �ڃx�N�g��
		//	UINT BoneIndex_[BONE_MAX_SIZE] = { 0 };			//!< �{�[���ԍ�.
		//	float BoneWeight_[BONE_MAX_SIZE] = { 0.0 };	//<! �{�[���E�F�C�g.
		//};

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
		* ���_���W��ǂݍ���.
		* 
		* @param vertexList	���_���X�g.
		* @param fbxMesh	FBXSDK�̃��b�V���N���X.
		*/
		void LoadPosition(vector<VertexBufferS>& vertexList, FbxMesh* fbxMesh);

		/**
		* �C���f�b�N�X���X�g���쐬����.
		*
		* @param indexList	�C���f�b�N�X���X�g.
		* @param fbxMesh	FBXSDK�̃��b�V���N���X.
		*/
		void CreateIndexList(vector<USHORT>& indexList, FbxMesh* fbxMesh);

		/**
		* �@�����쐬.
		*
		* @param vertexList	���_���X�g.
		* @param indexList	�C���f�b�N�X���X�g.
		*/
		void CreateNormal(vector<VertexBufferS>& vertexList, vector<USHORT>& indexList);

		/**
		* �ڃx�N�g�����쐬.
		*
		* @param vertexList	���_���X�g.
		*/
		void CreateTanget(vector<VertexBufferS>& vertexList);
		
		/**
		* UV���W��ǂݍ���.
		*/
		void LoadUV(vector<VertexBufferS>& vertexList, FbxMesh* fbxMesh);

		/**
		* �o�b�t�@�̍쐬.
		*
		* @param fbxMesh	FBXSDK�̃��b�V���N���X.
		*/
		//void CreateSkeletonBuffer(FbxMesh* fbxMesh);

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