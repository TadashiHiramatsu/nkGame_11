/**
 * 物理ワールドクラスの実装.
 */
#include"nkstdafx.h"
#include"nkPhysics.h"

namespace nkEngine
{

	/**
	 * 初期化.
	 */
	void Physics::Init()
	{
		//物理エンジンを初期化。
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

		//重力計算
		DynamicWorld_->setGravity(btVector3(0, -9.8, 0));
	}

	/**
	 * 更新.
	 */
	void Physics::Update()
	{
		DynamicWorld_->stepSimulation(Time().DeltaTime());
	}

	/**
	 * 解放.
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
	 * 剛体の追加.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @param rb	剛体.
	 */
	void Physics::AddRigidBody(RigidBody * rb)
	{
		DynamicWorld_->addRigidBody(rb->GetBody());
	}

	/**
	 * 剛体の削除.
	 *
	 * @param rb	剛体.
	 */
	void Physics::RemoveRigidBody(RigidBody * rb)
	{
		DynamicWorld_->removeRigidBody(rb->GetBody());
	}

}