/**
* �{�[���m�[�h�N���X�̒�`.
*/
#pragma once

#include"nkNode.h"

namespace nkEngine
{

	/**
	* �{�[���m�[�h�N���X.
	*/
	class BoneNode : public INode
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		BoneNode()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~BoneNode()
		{
		}

		/**
		* �쐬.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X.
		* @param parent		�e�̃|�C���^.
		* @param modelData	���f���f�[�^.
		*/
		void Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)override;

		/**
		* �{�[���ԍ���ݒ�.
		*/
		void SetBoneIndex(short index)
		{
			BoneIndex_ = index;
		}
		/**
		* �{�[���ԍ����擾.
		*/
		short GetBoneIndex()
		{
			return BoneIndex_;
		}

		/**
		* �����p���s���ݒ�.
		*/
		void SetBoneOffsetMatrix(const Matrix& offset)
		{
			BoneOffsetMatrix_ = offset;
		}

	private:

		/** �{�[���ԍ�. */
		short BoneIndex_ = -1;

		/** �{�[���̏����p���s��. */
		Matrix BoneOffsetMatrix_;

	};
}