/**
* 地面クラスの実装.
*/
#include"stdafx.h"
#include"Ground.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* 初期化.
*/
void Ground::Start()
{
	ModelRender_.Init("Ground", &Transform_, &g_MainLight->GetLight(), &g_MainCamera->GetCamera());
}

/**
* 更新.
*/
void Ground::Update()
{
	Transform_.Update();

	ModelRender_.Update();
}

/**
* Render前の描画.
*/
void Ground::PreRender()
{
	ModelRender_.PreRender();
}

/**
* 描画.
*/
void Ground::Render()
{
	ModelRender_.Render();
}
