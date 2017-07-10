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
	//モデル読み込み.
	ModelRender_.Init("MapObject_01", &Transform_, &g_MainLight->GetLight(), &g_MainCamera->GetCamera());
	ModelRender_.SetLimLight(true);
}

/**
* 更新.
*/
void MapChip::Update()
{
	Transform_.Update();

	ModelRender_.Update();
}

/**
* Render前の描画.
*/
void MapChip::PreRender()
{
	ModelRender_.PreRender();
}

/**
* 描画.
*/
void MapChip::Render()
{
	ModelRender_.Render();
}
