/**
* マップチップクラスの実装.
*/
#include"stdafx.h"
#include"MapChip.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* 初期化.
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
	//剛体の位置を更新。
	trans.setOrigin(btVector3(Transform_.Position_.x, Transform_.Position_.y, Transform_.Position_.z));

}

/**
* 更新.
*/
void MapChip::Update()
{
	btTransform& trans = RigidBody_.GetBody()->getWorldTransform();
	//剛体の位置を更新。
	trans.setOrigin(btVector3(Transform_.Position_.x, Transform_.Position_.y, Transform_.Position_.z));
}
