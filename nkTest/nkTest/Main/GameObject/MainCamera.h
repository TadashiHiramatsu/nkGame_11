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
	MainCamera(string name) : 
		IGameObject(name)
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
	Camera& GetCamera()
	{
		return Camera_;
	}

private:

	/**
	* �f�o�b�N��Ԃ̍X�V.
	*/
	void DebugUpdate();

private:

	/** �J�����N���X. */
	Camera Camera_;

	/** �J�����̋���. */
	float Distance_ = 10;

};
