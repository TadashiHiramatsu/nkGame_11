/**
* テストFBXオブジェクトクラスの実装.
*/
#include"stdafx.h"
#include"UnityChan.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* 初期化.
*/
void UnityChan::Start()
{
	ModelRender_.Init("UnityChan", &Transform_, &g_MainLight->GetLight(), &g_MainCamera->GetCamera());

	ModelRender_.SetLimLight(true);
}

/**
* 更新.
*/
void UnityChan::Update()
{
	static float angle = 0;
	//Transform_.Rotation_.RotationAxis(Vector3::Up, angle);
	angle -= 0.1f;

	Transform_.Update();

	ModelRender_.Update();
}

/**
* Render前の描画.
*/
void UnityChan::PreRender()
{
	ModelRender_.PreRender();
}

/**
* 描画.
*/
void UnityChan::Render()
{
	ModelRender_.Render();
}
