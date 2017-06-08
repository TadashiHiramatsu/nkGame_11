/**
* メインカメラクラスの実装.
*/
#include"stdafx.h"
#include"MainCamera.h"

/**
* 初期化.
*/
void MainCamera::Start()
{
	//カメラの視点の方向を設定.
	Camera_.SetPosDirection(Vector3(0.0f, 0.5f, -1.0f));

	//カメラの注視点を設定.
	Camera_.SetTarget(Vector3(0.0f, 0.0f, 0.0f));

	Distance_ = 10;
	Camera_.SetDistance(Distance_);

	Camera_.SetNear(0.01f);
	Camera_.SetFar(1000.0f);

	//更新
	Camera_.Update();
}

/**
* 更新.
*/
void MainCamera::Update()
{
	if(Input().GetKeyButton(KeyCodeE::Up))
	{
		Camera_.SpinVertically(-1);
	}
	if (Input().GetKeyButton(KeyCodeE::Down))
	{
		Camera_.SpinVertically(1);
	}
	if (Input().GetKeyButton(KeyCodeE::Left))
	{
		Camera_.SpinHorizontally(-1);
	}
	if (Input().GetKeyButton(KeyCodeE::Right))
	{
		Camera_.SpinHorizontally(1);
	}

	//カメラの更新.
	Camera_.Update();
}
