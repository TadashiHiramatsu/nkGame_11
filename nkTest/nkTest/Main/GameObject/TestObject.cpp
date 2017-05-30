/**
* テストオブジェクトクラスの実装.
*/
#include"stdafx.h"
#include"TestObject.h"

#include"TestCamera.h"

/**
* 初期化.
*/
void TestObject::Start()
{
	Vector3 dld = Vector3(0.0f, -1.0f, 1.0f);
	dld.Normalize();
	Light_.SetDiffuseLightDirection(0, dld);

	Box_.Create(&Transform_, &Light_, g_TestCamera->GetCamera());
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
}

/**
* 描画.
*/
void TestObject::Render()
{
	Box_.Render();
}
