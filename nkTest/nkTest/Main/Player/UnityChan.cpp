/**
* �e�X�gFBX�I�u�W�F�N�g�N���X�̎���.
*/
#include"stdafx.h"
#include"UnityChan.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* ������.
*/
void UnityChan::Start()
{
	ModelRender_.Init("UnityChan", &Transform_, &g_MainLight->GetLight(), &g_MainCamera->GetCamera());

	ModelRender_.SetLimLight(true);
}

/**
* �X�V.
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
* Render�O�̕`��.
*/
void UnityChan::PreRender()
{
	ModelRender_.PreRender();
}

/**
* �`��.
*/
void UnityChan::Render()
{
	ModelRender_.Render();
}
