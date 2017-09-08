/**
* �}�b�v�`�b�v�N���X�̎���.
*/
#include"stdafx.h"
#include"MapChip.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* ������.
*/
void MapChip::Start()
{
	BoxShape* Model_ = AddComponent<BoxShape>();
	MainCamera* camera = (MainCamera*)GameObjectManager().FindGameObject("MainCamera");
	MainLight* light = (MainLight*)GameObjectManager().FindGameObject("MainLight");
	Model_->Create(&light->GetLight(), &camera->GetCamera());

	Transform_.Position_.y = 2.0f;

	Collider_.Create(Vector3::One);
	RigidBodyInfoS info;
	info.Collider_ = &Collider_;
	info.Mass_ = 1.0f;
	RigidBody_.Create(info);
	RigidBody_.GetBody()->setUserIndex((int)ECollisionAttr::Character);
	RigidBody_.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	Engine().GetPhysics().AddRigidBody(&RigidBody_);

	btTransform& trans = RigidBody_.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(Transform_.Position_.x, Transform_.Position_.y, Transform_.Position_.z));

}

/**
* �X�V.
*/
void MapChip::Update()
{
	btTransform& trans = RigidBody_.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(Transform_.Position_.x, Transform_.Position_.y, Transform_.Position_.z));
}
