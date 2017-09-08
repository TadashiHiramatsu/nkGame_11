/**
 * ���̃N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkRigidBody.h"
#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * �쐬.
	 *
	 * @param rbInfo	���̏��.
	 */
	void RigidBody::Create(const RigidBodyInfoS& rbInfo)
	{
		//���
		Release();

		//�g�����X�t�H�[���쐬
		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(btVector3(rbInfo.Position_.x, rbInfo.Position_.y, rbInfo.Position_.z));
		transform.setRotation(btQuaternion(rbInfo.Rotation_.x, rbInfo.Rotation_.y, rbInfo.Rotation_.z, rbInfo.Rotation_.w));
		MotionState_ = new btDefaultMotionState;
		btRigidBody::btRigidBodyConstructionInfo btrbInfo(rbInfo.Mass_, MotionState_, rbInfo.Collider_->GetBody(), btVector3(0, 0, 0));

		//���̂��쐬�B
		RigidBody_ = new btRigidBody(btrbInfo);
	}

	/**
	* ���.
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