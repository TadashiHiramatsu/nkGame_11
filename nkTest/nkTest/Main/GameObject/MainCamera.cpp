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
	//�J�����̎��_�̕�����ݒ�.
	Camera_.SetPosDirection(Vector3(0.0f, 0.5f, -1.0f));

	//�J�����̒����_��ݒ�.
	Camera_.SetTarget(Vector3(0.0f, 0.0f, 0.0f));

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

	//�J�����̍X�V.
	Camera_.Update();
}
