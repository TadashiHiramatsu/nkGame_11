/**
* �e�X�g�I�u�W�F�N�g�N���X�̒�`.
*/
#pragma once

class TestObject : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	TestObject(string name) : 
		IGameObject(name)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~TestObject()
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
	* �`��.
	*/
	void Render()override;

private:

	/** ���f���N���X. */
	ModelRender Model_;

};