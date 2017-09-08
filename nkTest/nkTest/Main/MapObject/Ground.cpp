/**
* ’n–ÊƒNƒ‰ƒX‚ÌÀ‘•.
*/
#include"stdafx.h"
#include"Ground.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* ‰Šú‰».
*/
void Ground::Start()
{
	ModelData* modelData = AddComponent<ModelData>();
	modelData->Load("Ground");
	ModelRender* modelRender = AddComponent<ModelRender>();
	MainCamera* camera = (MainCamera*)GameObjectManager().FindGameObject("MainCamera");
	MainLight* light = (MainLight*)GameObjectManager().FindGameObject("MainLight");
	modelRender->Start(&light->GetLight(), &camera->GetCamera());

	Transform_.Update();
	Collider_.Create(modelData, &Transform_.WorldMatrix_);
	RigidBodyInfoS info;
	info.Collider_ = &Collider_;
	info.Mass_ = 0.0f;
	RigidBody_.Create(info);
	RigidBody_.GetBody()->setUserIndex((int)ECollisionAttr::Ground);
	Engine().GetPhysics().AddRigidBody(&RigidBody_);

}
