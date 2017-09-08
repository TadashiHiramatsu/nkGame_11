/**
* �X�P���g���N���X�̒�`.
*/
#pragma once

#include"nkBoneNode.h"

namespace nkEngine
{

	/**
	* �X�P���g���N���X.
	* ���i��\��.
	*/
	class Skeleton : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Skeleton()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~Skeleton()
		{
		}

		/**
		* �{�[�����擾.
		*
		* @param index	�{�[���ԍ�.
		*/
		BoneNode* GetBone(UINT index)
		{
			return BoneList_[index];
		}
		/**
		* �{�[�����擾.
		*
		* @param name	�{�[����.
		*/
		BoneNode* FindBone(string name)
		{
			auto node = find_if(BoneList_.begin(), BoneList_.end(), [name](BoneNode* bone) {return bone->GetName() == name; });
			if (node != BoneList_.end())
			{
				return (*node);
			}
			return nullptr;
		}

		/**
		* �{�[����ݒ�.
		*
		* @param bone	�{�[���|�C���^.
		*/
		void AddBone(BoneNode* bone)
		{
			//�{�[���ԍ���ݒ�.
			bone->SetBoneIndex(BoneList_.size());
			//���X�g�ɓo�^.
			BoneList_.push_back(bone);
		}

		/**
		* �{�[���ԍ����擾.
		* ���݂��Ă���΃{�[���ԍ�.
		* ���݂��ĂȂ����-1��Ԃ�.
		*
		* @param name	�{�[����.
		*/
		int FindBoneIndex(string name)
		{
			auto node = find_if(BoneList_.begin(), BoneList_.end(), [name](BoneNode* bone) {return bone->GetName() == name; });
			if (node != BoneList_.end())
			{
				return (*node)->GetBoneIndex();
			}
			return -1;
		}

	private:

		/**
		* �{�[�����X�g.
		*/
		vector<BoneNode*> BoneList_;

	};

}