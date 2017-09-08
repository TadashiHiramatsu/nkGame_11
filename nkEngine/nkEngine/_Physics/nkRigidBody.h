/**
 * 剛体クラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * 剛体情報.
	 */
	struct RigidBodyInfoS : Noncopyable
	{
	public:

		/** 座標. */
		Vector3 Position_ = Vector3::Zero;
		/** 回転. */
		Quaternion Rotation_ = Quaternion::Identity;
		/** コライダー. */
		ICollider* Collider_ = nullptr;
		/** 質量. */
		float Mass_ = 0.0f;

	};

	/**
	 * 剛体クラス.
	 */
	class RigidBody : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 */
		RigidBody()
		{
		}

		/**
		 * デストラクタ.
		 */
		~RigidBody()
		{
			Release();
		}

		/**
		 * 作成.
		 *
		 * @param rbInfo	剛体情報.
		 */
		void Create(const RigidBodyInfoS& rbInfo);

		/**
		 * 解放.
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

		/** 剛体. */
		btRigidBody* RigidBody_ = nullptr;
		/** モーションステート. */
		btDefaultMotionState* MotionState_ = nullptr;
	
	};

}