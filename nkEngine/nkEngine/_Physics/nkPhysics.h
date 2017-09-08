/**
 * 物理ワールドクラスの定義.
 */
#pragma once

#include"nkRigidBody.h"

namespace nkEngine
{

	/**
	 * 物理ワールドクラス.
	 */
	class Physics : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 */
		Physics()
		{
		}

		/**
		 * デストラクタ.
		 */
		~Physics()
		{
			Release();
		}

		/**
		 * 初期化.
		 */
		void Init();

		/**
		 * 更新.
		 */
		void Update();

		/**
		 * 開放.
		 */
		void Release();

		/**
		 * ダイナミックワールドの取得.
		 */
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return DynamicWorld_;
		}

		/**
		 * 剛体の追加.
		 *
		 * @param rb	剛体.
		 */
		void AddRigidBody(RigidBody* rb);

		/**
		 * 剛体の削除.
		 *
		 * @param rb	剛体.
		 */
		void RemoveRigidBody(RigidBody* rb);

		/**
		 * 凸面一掃？.
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

		/** 衝突判定配置. */
		btDefaultCollisionConfiguration* CollisionConfiguration_ = nullptr;
		/** 衝突解決処理. */
		btCollisionDispatcher* CollisionDispatcher_ = nullptr;
		/** ブロードフェーズ。衝突判定の枝切り. */
		btBroadphaseInterface* OverlappingPairCache_ = nullptr;
		/** コンストレイントソルバー。拘束条件の解決処理. */
		btSequentialImpulseConstraintSolver* ConstraintSolver_ = nullptr;
		/** ワールド. */
		btDiscreteDynamicsWorld* DynamicWorld_ = nullptr;

	};

}