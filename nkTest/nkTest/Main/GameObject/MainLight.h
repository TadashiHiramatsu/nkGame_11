/**
* ���C�����C�g�N���X�̒�`.
*/
#pragma once

/**
* ���C�����C�g�N���X.
*/
class MainLight : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	MainLight(string name) : 
		IGameObject(name)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~MainLight()
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
	* ���C�g���擾.
	*/
	Light& GetLight()
	{
		return Light_;
	}

private:

	/** ���C�g�N���X. */
	Light Light_;

};
