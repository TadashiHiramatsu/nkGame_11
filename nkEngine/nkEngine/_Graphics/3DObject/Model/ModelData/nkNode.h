/**
* �m�[�h�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	class ModelData;

	/**
	* �m�[�h�N���X.
	*/
	class INode : public IGameObject
	{
	public:

		/**
		* �m�[�h�^�C�v�R�[�h.
		*/
		enum class NodeTypeE
		{
			Unknown,	//!< �A���m�E��.
			Null,		//!< �k��.
			Mesh,		//!< ���b�V��.
			SkinMesh,	//!< �X�L�����b�V��.
			Bone,		//!< �{�[��.
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		INode()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~INode()
		{
		}

		/**
		* �쐬.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X.
		* @param parent		�e�̃|�C���^.
		* @param modelData	���f���f�[�^.
		*/
		virtual void Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData);

		/**
		* �X�V.
		*/
		virtual void Update();

		/**
		* �m�[�h�^�C�v���擾.
		*/
		NodeTypeE GetNodeType() const
		{
			return NodeType_;
		}

	protected:

		/** �m�[�h�^�C�v. */
		NodeTypeE NodeType_ = NodeTypeE::Unknown;

	};

}