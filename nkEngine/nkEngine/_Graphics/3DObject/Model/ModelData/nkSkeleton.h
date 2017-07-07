/**
* �X�P���g���N���X�̒�`.
*/
#pragma once

#include"nkBone.h"

namespace nkEngine
{

	/** �{�[�����X�g. */
	using BoneList = vector<BonePtr>;

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
		* �A�j���[�V�����G���h�t���[����ݒ�.
		*
		* @param frame	�t���[���ԍ�.
		*/
		void SetAnimationEndFrame(UINT frame)
		{
			AnimationEndFrame_ = frame;
		}
		/**
		* �A�j���[�V�����G���h�t���[�����擾.
		*/
		UINT GetAnimationEndFrame()
		{
			return AnimationEndFrame_;
		}

		/**
		* ���݂̃A�j���[�V�����t���[���ԍ���ݒ�.
		*/
		void SetAnimationFrame(UINT frame)
		{
			NowAnimationFrame_ = frame;
		}
		/**
		* ���݂̃A�j���[�V�����t���[���ԍ����擾.
		*/
		UINT GetAnimationFrame()
		{
			return NowAnimationFrame_;
		}
		
		/**
		* �{�[�����擾.
		*
		* @param index	�{�[���ԍ�.
		*/
		BonePtr GetBone(UINT index)
		{
			return BoneList_[index];
		}
		/**
		* �{�[�����擾.
		*
		* @param name	�{�[����.
		*/
		BonePtr GetBone(string name)
		{
			for (auto& it : BoneList_)
			{
				if (it->GetBoneName() == name)
				{
					return it;
				}
			}
			return nullptr;
		}

		/**
		* �{�[����ݒ�.
		*
		* @param bone	�{�[���|�C���^.
		*/
		void AddBone(BonePtr bone)
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
			for (auto& it : BoneList_)
			{
				if (it->GetBoneName() == name)
				{
					return it->GetBoneIndex();
				}
			}
			return -1;
		}

	private:

		/**
		* �{�[�����X�g.
		*/
		BoneList BoneList_;

		/** �A�j���[�V�����G���h�t���[��. */
		UINT AnimationEndFrame_ = 0;
		/** ���݂̃A�j���[�V�����t���[���ԍ�. */
		UINT NowAnimationFrame_ = 0;

	};

}