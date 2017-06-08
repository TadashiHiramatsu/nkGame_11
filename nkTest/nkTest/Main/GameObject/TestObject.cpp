/**
* テストオブジェクトクラスの実装.
*/
#include"stdafx.h"
#include"TestObject.h"

#include"MainCamera.h"
#include"MainLight.h"

/**
* 初期化.
*/
void TestObject::Start()
{
	Model_.Init("Building_a",&Transform_, &g_MainLight->GetLight(), g_MainCamera->GetCamera());
}

/**
* 更新.
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
* 描画.
*/
void TestObject::Render()
{
	Model_.Render();
}
