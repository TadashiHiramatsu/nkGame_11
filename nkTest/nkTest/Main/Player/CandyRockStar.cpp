/**
* CandyRockStarクラスの実装.
*/
#include"stdafx.h"
#include"CandyRockStar.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* 初期化.
*/
void CandyRockStar::Start()
{
	ModelData* modelData = AddComponent<ModelData>();
	modelData->Load("CandyRockStar");
	modelData->FindNode("cheek")->SetActive(false);
	ModelRender* modelRender = AddComponent<ModelRender>();
	MainCamera* camera = (MainCamera*)GameObjectManager().FindGameObject("MainCamera");
	MainLight* light = (MainLight*)GameObjectManager().FindGameObject("MainLight");
	modelRender->Start(&light->GetLight(), &camera->GetCamera());
	modelRender->SetLimLight(true);

	Transform_.Rotation_.RotationEuler(Vector3(0.0f, 180.0f, 0.0f));
}

/**
* 更新.
*/
void CandyRockStar::Update()
{
	ModelData* model = (ModelData*)FindComponent("ModelData");

	static float angle = 0;
	//Transform_.Rotation_.RotationAxis(Vector3::Up, angle);
	angle -= 0.1f;

}
