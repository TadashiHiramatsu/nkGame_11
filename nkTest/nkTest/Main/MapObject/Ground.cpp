/**
* �n�ʃN���X�̎���.
*/
#include"stdafx.h"
#include"Ground.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* ������.
*/
void Ground::Start()
{
	ModelRender_.Init("Ground", &Transform_, &g_MainLight->GetLight(), &g_MainCamera->GetCamera());
}

/**
* �X�V.
*/
void Ground::Update()
{
	Transform_.Update();

	ModelRender_.Update();
}

/**
* Render�O�̕`��.
*/
void Ground::PreRender()
{
	ModelRender_.PreRender();
}

/**
* �`��.
*/
void Ground::Render()
{
	ModelRender_.Render();
}
