/**
 * �������[���h�N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkPhysics.h"

namespace nkEngine
{

	/**
	 * ������.
	 */
	void Physics::Init()
	{
		//�����G���W�����������B
		CollisionConfiguration_ = new btDefaultCollisionConfiguration();

		CollisionDispatcher_ = new	btCollisionDispatcher(CollisionConfiguration_);

		OverlappingPairCache_ = new btDbvtBroadphase();

		ConstraintSolver_ = new btSequentialImpulseConstraintSolver;

		DynamicWorld_ = new btDiscreteDynamicsWorld(
			CollisionDispatcher_,
			OverlappingPairCache_,
			ConstraintSolver_,
			CollisionConfiguration_
		);

		//�d�͌v�Z
		DynamicWorld_->setGravity(btVector3(0, -9.8, 0));
	}

	/**
	 * �X�V.
	 */
	void Physics::Update()
	{
		DynamicWorld_->stepSimulation(Time().DeltaTime());
	}

	/**
	 * ���.
	 */
	void Physics::Release()
	{
		if (DynamicWorld_)
		{
			delete DynamicWorld_;
			DynamicWorld_ = nullptr;
		}
		if (ConstraintSolver_)
		{
			delete ConstraintSolver_;
			ConstraintSolver_ = nullptr;
		}
		if (OverlappingPairCache_)
		{
			delete OverlappingPairCache_;
			OverlappingPairCache_ = nullptr;
		}
		if (CollisionDispatcher_)
		{
			delete CollisionDispatcher_;
			CollisionDispatcher_ = nullptr;
		}
		if (CollisionConfiguration_)
		{
			delete CollisionConfiguration_;
			CollisionConfiguration_ = nullptr;
		}
	}

	/**
	 * ���̂̒ǉ�.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param rb	����.
	 */
	void Physics::AddRigidBody(RigidBody * rb)
	{
		DynamicWorld_->addRigidBody(rb->GetBody());
	}

	/**
	 * ���̂̍폜.
	 *
	 * @param rb	����.
	 */
	void Physics::RemoveRigidBody(RigidBody * rb)
	{
		DynamicWorld_->removeRigidBody(rb->GetBody());
	}

}