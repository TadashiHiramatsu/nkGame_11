/**
* �e�X�g�I�u�W�F�N�g�N���X�̎���.
*/
#include"stdafx.h"
#include"TestObject.h"

#include"MainCamera.h"
#include"MainLight.h"

/**
* ������.
*/
void TestObject::Start()
{
	Model_.Init("Building_a",&Transform_, &g_MainLight->GetLight(), g_MainCamera->GetCamera());
}

/**
* �X�V.
*/
void TestObject::Update()
{
	static float angle = 0;
	Transform_.Rotation_.RotationAxis(Vector3::Up, angle);
	angle += 0.1f;

	Transform_.Update();

	Model_.Update();
}

/**
* �`��.
*/
void TestObject::Render()
{
	Model_.Render();
}
