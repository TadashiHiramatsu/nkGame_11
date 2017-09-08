/**
 * 剛体クラスの実装.
 */
#include"nkstdafx.h"
#include"nkRigidBody.h"
#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * 作成.
	 *
	 * @param rbInfo	剛体情報.
	 */
	void RigidBody::Create(const RigidBodyInfoS& rbInfo)
	{
		//解放
		Release();

		//トランスフォーム作成
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(rbInfo.Position_.x, rbInfo.Position_.y, rbInfo.Position_.z));
		transform.setRotation(btQuaternion(rbInfo.Rotation_.x, rbInfo.Rotation_.y, rbInfo.Rotation_.z, rbInfo.Rotation_.w));
		MotionState_ = new btDefaultMotionState;
		btRigidBody::btRigidBodyConstructionInfo btrbInfo(rbInfo.Mass_, MotionState_, rbInfo.Collider_->GetBody(), btVector3(0, 0, 0));

		//剛体を作成。
		RigidBody_ = new btRigidBody(btrbInfo);
	}

	/**
	* 解放.
	*/
	void RigidBody::Release()
	{
		if (RigidBody_)
		{
			delete RigidBody_;
			RigidBody_ = nullptr;
		}
		if (MotionState_)
		{
			delete MotionState_;
			MotionState_ = nullptr;
		}
	}

}