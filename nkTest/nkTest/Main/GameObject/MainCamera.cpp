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
	//1人称カメラに設定.
	Camera_.SetCameraType(Camera::CameraTypeCodeE::FirstPerson);

	//カメラの視線ベクトルを設定.
	Camera_.SetDirection(Vector3::Front);

	//カメラの視点を設定.
	Camera_.SetPosition(Vector3(0.0f, 1.0f, -1.0f));

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
	//デバック状態の更新.
	DebugUpdate();
}

/**
* デバック状態の更新.
*/
void MainCamera::DebugUpdate()
{

	//カメラの視線ベクトル.
	Vector3 direction = Camera_.GetDirection();
	direction.Normalize();

	//カメラの視点.
	Vector3 position = Camera_.GetPosition();

	//ホイールの力.
	float wheelPower = Input().GetMouseWheel();
	wheelPower *= 0.01f;

	//1秒間の移動速度.
	static float SPEED = 2.0f;
	Vector3 wheelMove = direction;
	wheelMove.Scale(wheelPower * SPEED * Time().DeltaTime() * -1);
	position.Add(wheelMove);

	Vector2 mouseMove = Input().GetMouseMove();

	if (Input().GetMoudeButton(MouseButtonE::Wheel))
	{
		//横.
		Vector3 side = Vector3(direction.z, 0.0f, -direction.x);
		//縦.
		Vector3 hei;
		hei.Cross(side, direction);

		Vector3 move = Vector3::Zero;

		side.Scale(mouseMove.x);
		hei.Scale(mouseMove.y);

		move.Add(side, hei);

		move.Scale(Time().DeltaTime() * 0.5f);
		position.Add(move);
	}
	if (Input().GetMoudeButton(MouseButtonE::Right))
	{
		static float SPIN_SPEED = 3.0f;
		Camera_.SpinHorizontally(-mouseMove.x * Time().DeltaTime() * SPIN_SPEED);
		Camera_.SpinVertically(mouseMove.y * Time().DeltaTime() * SPIN_SPEED);
	}

	Camera_.SetPosition(position);

	//カメラクラスの更新.
	Camera_.Update();
}
