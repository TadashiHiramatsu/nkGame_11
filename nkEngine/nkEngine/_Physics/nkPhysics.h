/**
 * �������[���h�N���X�̒�`.
 */
#pragma once

#include"nkRigidBody.h"

namespace nkEngine
{

	/**
	 * �������[���h�N���X.
	 */
	class Physics : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		Physics()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~Physics()
		{
			Release();
		}

		/**
		 * ������.
		 */
		void Init();

		/**
		 * �X�V.
		 */
		void Update();

		/**
		 * �J��.
		 */
		void Release();

		/**
		 * �_�C�i�~�b�N���[���h�̎擾.
		 */
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return DynamicWorld_;
		}

		/**
		 * ���̂̒ǉ�.
		 *
		 * @param rb	����.
		 */
		void AddRigidBody(RigidBody* rb);

		/**
		 * ���̂̍폜.
		 *
		 * @param rb	����.
		 */
		void RemoveRigidBody(RigidBody* rb);

		/**
		 * �ʖʈ�|�H.
		 *
		 * @param 		  	castShape			 	The cast shape.
		 * @param 		  	convexFromWorld		 	The convex from world.
		 * @param 		  	convexToWorld		 	The convex to world.
		 * @param [in,out]	resultCallback		 	The result callback.
		 * @param 		  	allowedCcdPenetration	(Optional) The allowed CCD penetration.
		 */
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
		)
		{
			DynamicWorld_->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}

	private:

		/** �Փ˔���z�u. */
		btDefaultCollisionConfiguration* CollisionConfiguration_ = nullptr;
		/** �Փˉ�������. */
		btCollisionDispatcher* CollisionDispatcher_ = nullptr;
		/** �u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�. */
		btBroadphaseInterface* OverlappingPairCache_ = nullptr;
		/** �R���X�g���C���g�\���o�[�B�S�������̉�������. */
		btSequentialImpulseConstraintSolver* ConstraintSolver_ = nullptr;
		/** ���[���h. */
		btDiscreteDynamicsWorld* DynamicWorld_ = nullptr;

	};

}