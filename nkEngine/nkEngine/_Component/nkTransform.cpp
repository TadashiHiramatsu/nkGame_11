/**
 * �g�����X�t�H�[���N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkTransform.h"

namespace nkEngine
{

	/**
	 * �X�V.
	 */
	void Transform::Update()
	{
		Matrix mTrans, mScale;

		//�ړ��s��̌v�Z
		mTrans.MakeTranslation(Position_);
		//��]�s��̌v�Z
		RotationMatrix_.MakeRotationQuaternion(Rotation_);
		//�g��s��̌v�Z
		mScale.MakeScaling(Scale_);

		//���[�J���s����v�Z
		LocalMatrix_.Mul(mScale, RotationMatrix_);
		LocalMatrix_.Mul(LocalMatrix_, mTrans);

		//�e�q�֌W���v�Z
		if (Parent_)
		{
			WorldMatrix_.Mul(LocalMatrix_, Parent_->WorldMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//���[���h�s��̋t�s����v�Z
		WorldInvMatrix_.Inverse(WorldMatrix_);
	
	}

	/**
	* �r���{�[�h����X�V.
	*/
	void Transform::BillboardUpdate(const Matrix& rot)
	{
		Matrix mTrans, mScale;

		//�ړ��s��̌v�Z
		mTrans.MakeTranslation(Position_);

		//�N�H�[�^�j�I��.
		Quaternion qRot;

		float s;
		s = sin(0);
		qRot.x = rot.m[2][0] * s;
		qRot.y = rot.m[2][1] * s;
		qRot.z = rot.m[2][2] * s;
		qRot.w = cos(0);

		//��]�s��.
		Matrix mRot;
		mRot.MakeRotationQuaternion(qRot);

		RotationMatrix_.Mul(rot, mRot);

		//�g��s��̌v�Z
		mScale.MakeScaling(Scale_);

		//���[�J���s����v�Z
		LocalMatrix_.Mul(mScale, RotationMatrix_);
		LocalMatrix_.Mul(LocalMatrix_, mTrans);

		//�e�q�֌W���v�Z
		if (Parent_)
		{
			WorldMatrix_.Mul(LocalMatrix_, Parent_->WorldMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//���[���h�s��̋t�s����v�Z
		WorldInvMatrix_.Inverse(WorldMatrix_);

	}

}// namespace nkEngine