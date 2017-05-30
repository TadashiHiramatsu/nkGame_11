/**
 * �g�����X�t�H�[���N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �g�����X�t�H�[���N���X.
	 */
	class Transform : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		Transform()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~Transform()
		{
		}

		/**
		 * ���[���h�s��Ȃǂ̍X�V.
		 */
		void Update();

		/**
		 * �r���{�[�h����X�V.
		 */
		void BillboardUpdate(const Matrix& rot);
	
	public:

		/** �e�̃g�����X�t�H�[��. */
		Transform* Parent_ = nullptr;

		/** �ʒu�x�N�g��. */
		Vector3 Position_ = Vector3::Zero;
		/** �g��x�N�g��. */
		Vector3 Scale_ = Vector3::One;
		/** ��]�x�N�g��. */
		Quaternion Rotation_ = Quaternion::Identity;

		/** ���[�J���̃��[���h�s��. */
		Matrix LocalMatrix_ = Matrix::Identity;
		/** ���[���h�s��. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** ���[���h�s��̋t�s��. */
		Matrix WorldInvMatrix_ = Matrix::Identity;
		/** ��]�s��. */
		Matrix RotationMatrix_ = Matrix::Identity;

	};

}// namespace nkEngine