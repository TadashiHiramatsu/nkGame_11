/**
 * ���̃N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * ���̏��.
	 */
	struct RigidBodyInfoS : Noncopyable
	{
	public:

		/** ���W. */
		Vector3 Position_ = Vector3::Zero;
		/** ��]. */
		Quaternion Rotation_ = Quaternion::Identity;
		/** �R���C�_�[. */
		ICollider* Collider_ = nullptr;
		/** ����. */
		float Mass_ = 0.0f;

	};

	/**
	 * ���̃N���X.
	 */
	class RigidBody : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		RigidBody()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~RigidBody()
		{
			Release();
		}

		/**
		 * �쐬.
		 *
		 * @param rbInfo	���̏��.
		 */
		void Create(const RigidBodyInfoS& rbInfo);

		/**
		 * ���.
		 */
		void Release();

		/**
		 * Gets the body.
		 */
		btRigidBody* GetBody()
		{
			return RigidBody_;
		}

	private:

		/** ����. */
		btRigidBody* RigidBody_ = nullptr;
		/** ���[�V�����X�e�[�g. */
		btDefaultMotionState* MotionState_ = nullptr;
	
	};

}