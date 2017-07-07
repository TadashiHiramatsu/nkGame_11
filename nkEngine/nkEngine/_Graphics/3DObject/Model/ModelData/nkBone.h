/**
* �{�[���N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/** �{�[���N���X. */
	class Bone;
	/** �{�[���N���X�̃V�F�A�[�h�|�C���^. */
	using BonePtr = shared_ptr<Bone>;

	/** �s��z��. */
	using MatrixList = vector<Matrix>;

	/** �C���f�b�N�X�z��. */
	using IndexList = vector<USHORT>;

	/**
	* �{�[���N���X.
	*/
	class Bone : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Bone()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~Bone()
		{
		}

		/**
		* �{�[������ݒ�.
		*/
		void SetBoneName(string name)
		{
			BoneName_ = name;
		}
		/**
		* �{�[�������擾.
		*/
		string GetBoneName()
		{
			return BoneName_;
		}

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
		* �e�̃{�[���ԍ���ݒ�.
		*/
		void SetParentBoneIndex(short index)
		{
			ParentBoneIndex_ = index;
		}
		/**
		* �e�̃{�[���ԍ����擾.
		*/
		short GetParentBoneIndex()
		{
			return ParentBoneIndex_;
		}

		/**
		* �q���{�[����ǉ�.
		*
		* @param bone	�q���{�[���A�h���X.
		*/
		void AddChildBoneIndex(BonePtr bone)
		{
			bone->SetParentBoneIndex(BoneIndex_);
			ChildBoneIndexList_.push_back(bone->GetBoneIndex());
		}
		/**
		* �q���{�[���ԍ����X�g���擾.
		*/
		const IndexList& GetChildBoneIndexList()
		{
			return ChildBoneIndexList_;
		}

		/**
		* 1�t���[���̍s���ݒ�.
		*
		* @param matrix	�s��.
		* @param frame	�t���[���ԍ�.
		*/
		void SetAnimationMatrix(const Matrix& matrix, USHORT frame)
		{
			AnimationMatrixList_[frame] = matrix;
		}

		/**
		* �A�j���[�V�����s�񃊃X�g���擾.
		*/
		const MatrixList& GetAnimationMatrix() const
		{
			return AnimationMatrixList_;
		}

	private:

		/** �{�[����. */
		string BoneName_ = "";
		/** �{�[���ԍ�. */
		short BoneIndex_ = -1;

		/** �e�̃{�[���ԍ����X�g. */
		short ParentBoneIndex_ = -1;
		/** �q���̃{�[���ԍ����X�g. */
		IndexList ChildBoneIndexList_;

		/** 
		* �A�j���[�V�������̍s�񃊃X�g.
		* �t���[���P�ʂœo�^����Ă���.
		*/
		MatrixList AnimationMatrixList_;

	};
}