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

		if (CalcType_ == CalcTypeCodeE::DirDistance)
		{
			//�����x�N�g���𐳋K��.
			Direction_.Normalize();
			
			switch (CameraType_)
			{
			case CameraTypeCodeE::FirstPerson:
				
				//���_�Ǝ������璍���_���v�Z.
				Target_.Add(Direction_, Position_);
				
				break;
			case CameraTypeCodeE::ThirdPerson:

				//�����ɋ�������Z.
				Direction_.Scale(Distance_);
				
				//�t�������王�_���v�Z.
				Position_.Add(Direction_, Target_);

				break;
			default:
				break;
			}

		}

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
		if (CalcType_ == CalcTypeCodeE::DirDistance)
		{
			Matrix tmp = Matrix::Identity;

			//�s���Y�����ɉ�].
			tmp.MakeRotationY(angle);

			//���K��.
			Direction_.Normalize();
			//�����x�N�g���ɔ��f.
			Direction_.TransformCoord(tmp);
		}
	}

	/**
	* �c��].
	*
	* @param angle ��]��(�x).
	*/
	void Camera::SpinVertically(float angle)
	{
		if (CalcType_ == CalcTypeCodeE::DirDistance)
		{
			//�N�H�[�^�j�I��.
			Quaternion qua = Quaternion::Identity;
			//��]�s��.
			Matrix tmp = Matrix::Identity;

			//���K��.
			Direction_.Normalize();

			//�������x�N�g��.
			Vector3 side = Vector3::Zero;
			side.x = -Direction_.z;
			side.z = Direction_.x;

			//�N�H�[�^�j�I�����������ɉ�].
			qua.RotationAxis(side, angle);

			//�s����N�H�[�^�j�I���ɂ���].
			tmp.MakeRotationQuaternion(qua);

			//�����x�N�g���ɔ��f.
			Direction_.TransformCoord(tmp);
		}
	}

}