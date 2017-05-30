/**
* �J�����N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkCamera.h"

namespace nkEngine
{

	/**
	* �X�V.
	*/
	void Camera::Update()
	{
		//�A�X�y�N�g��̌v�Z
		Aspect_ = (float)Engine().GetFrameW() / (float)Engine().GetFrameH();

		//�v���W�F�N�V�����s��̌v�Z
		ProjMatrix_.MakeProjectionFovLH(Angle_, Aspect_, Near_, Far_);

		//�|�W�V���������̌v�Z
		PosDirection_.Normalize();

		//�|�W�V�����̌v�Z
		PosDirection_.Scale(Distance_);
		Position_.Add(PosDirection_, Target_);

		//�r���[�s��̌v�Z
		ViewMatrix_.MakeLookAtLH(Position_, Target_, Up_);

		//�r���[�s��̋t�s����v�Z
		ViewInvMatrix_.Inverse(ViewMatrix_);

		//��]�s����v�Z
		RotationMatrix_ = ViewInvMatrix_;
		RotationMatrix_.m[3][0] = 0.0f;
		RotationMatrix_.m[3][1] = 0.0f;
		RotationMatrix_.m[3][2] = 0.0f;
		RotationMatrix_.m[3][3] = 1.0f;

		//��]�s��̋t�s����v�Z
		RotationInvMatrix_.Transpose(RotationMatrix_);
	}

	/**
	* ����].
	*
	* @param angle ��]��(�x).
	*/
	void Camera::SpinHorizontally(float angle)
	{
		Matrix tmp = Matrix::Identity;

		//�s���Y�����ɉ�].
		tmp.MakeRotationY(angle);

		PosDirection_.Normalize();

		//�x�N�g���ɔ��f.
		PosDirection_.TransformCoord(tmp);
	}

	/**
	* �c��].
	*
	* @param angle ��]��(�x).
	*/
	void Camera::SpinVertically(float angle)
	{
		//�N�H�[�^�j�I��.
		Quaternion qua = Quaternion::Identity;
		//��]�s��.
		Matrix tmp = Matrix::Identity;

		PosDirection_.Normalize();

		//�������x�N�g��.
		Vector3 side = Vector3::Zero;
		side.x = -PosDirection_.z;
		side.z = PosDirection_.x;

		//�N�H�[�^�j�I�����������ɉ�].
		qua.RotationAxis(side, angle);

		//�s����N�H�[�^�j�I���ɂ���].
		tmp.MakeRotationQuaternion(qua);

		//�x�N�g���ɔ��f.
		PosDirection_.TransformCoord(tmp);
	}

	/**
	* �C�ӎ����̉�].
	*
	* @param vec	�C�ӂ̎�.
	* @param angle	��]��(�x).
	*/
	void Camera::SpinAxis(Vector3 & vec, float angle)
	{
		//�N�H�[�^�j�I��.
		Quaternion qua = Quaternion::Identity;
		//��]�s��.
		Matrix tmp = Matrix::Identity;

		//�N�H�[�^�j�I����C�ӎ����ɉ�].
		qua.RotationAxis(vec, angle);

		//�s����N�H�[�^�j�I���ɂ���].
		tmp.MakeRotationQuaternion(qua);

		//�x�N�g���ɔ��f.
		PosDirection_.TransformCoord(tmp);
	}

}