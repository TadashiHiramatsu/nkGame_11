/**
* ���C���J�����N���X�̎���.
*/
#include"stdafx.h"
#include"MainCamera.h"

/**
* ������.
*/
void MainCamera::Start()
{
	//1�l�̃J�����ɐݒ�.
	Camera_.SetCameraType(Camera::CameraTypeCodeE::FirstPerson);

	//�J�����̎����x�N�g����ݒ�.
	Camera_.SetDirection(Vector3::Front);

	//�J�����̎��_��ݒ�.
	Camera_.SetPosition(Vector3(0.0f, 1.0f, -1.0f));

	Distance_ = 10;
	Camera_.SetDistance(Distance_);

	Camera_.SetNear(0.01f);
	Camera_.SetFar(1000.0f);

	//�X�V
	Camera_.Update();
}

/**
* �X�V.
*/
void MainCamera::Update()
{
	//�f�o�b�N��Ԃ̍X�V.
	DebugUpdate();
}

/**
* �f�o�b�N��Ԃ̍X�V.
*/
void MainCamera::DebugUpdate()
{

	//�J�����̎����x�N�g��.
	Vector3 direction = Camera_.GetDirection();
	direction.Normalize();

	//�J�����̎��_.
	Vector3 position = Camera_.GetPosition();

	//�z�C�[���̗�.
	float wheelPower = Input().GetMouseWheel();
	wheelPower *= 0.01f;

	//1�b�Ԃ̈ړ����x.
	static float SPEED = 2.0f;
	Vector3 wheelMove = direction;
	wheelMove.Scale(wheelPower * SPEED * Time().DeltaTime() * -1);
	position.Add(wheelMove);

	Vector2 mouseMove = Input().GetMouseMove();

	if (Input().GetMoudeButton(MouseButtonE::Wheel))
	{
		//��.
		Vector3 side = Vector3(direction.z, 0.0f, -direction.x);
		//�c.
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

	//�J�����N���X�̍X�V.
	Camera_.Update();
}
