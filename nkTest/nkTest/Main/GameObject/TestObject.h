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
	TestObject()
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

	void SetParent(Transform* p)
	{
		Transform_.Parent_ = p;
	}

private:

	/** ���C�g�N���X. */
	Light Light_;

	/** �{�b�N�X�`��. */
	BoxShape Box_;

};