/**
* �e�X�gFBX�I�u�W�F�N�g�N���X�̒�`.
*/
#pragma once

/**
* �e�X�gFBX�I�u�W�F�N�g�N���X��.
*/
class UnityChan : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	UnityChan(string name) :
		IGameObject(name)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~UnityChan()
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
	* Render�O�̕`��.
	*/
	void PreRender()override;

	/**
	* �`��.
	*/
	void Render()override;

private:

	/** ���f���`��N���X. */
	ModelRender ModelRender_;

};