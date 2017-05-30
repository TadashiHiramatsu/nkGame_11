/**
* ���C���J�����N���X�̒�`.
*/
#pragma once

/**
* ���C���J�����N���X.
*/
class MainCamera : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	MainCamera()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~MainCamera()
	{
	}

	/**
	* ������.
	*/
	void Start()override;

	/**
	* �X�V.
	*/
	void Update()override;

	/**
	* �J�������擾.
	*
	* @return	�J�����N���X.
	*/
	Camera* GetCamera()
	{
		return &Camera_;
	}

	/**
	* �O�������擾.
	*/
	const Vector3& GetFront()
	{
		Vector3 front;
		front.Sub(Camera_.GetTarget(), Camera_.GetPosition());
		front.Normalize();
		return front;
	}

private:

	/** �J�����N���X. */
	Camera Camera_;

	/** �J�����̋���. */
	float Distance_ = 10;

};

/** �O���[�o��. */
extern MainCamera* g_MainCamera;