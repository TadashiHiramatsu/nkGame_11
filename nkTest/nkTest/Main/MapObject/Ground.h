/**
* �n�ʃN���X�̒�`.
*/
#pragma once

/**
* �n�ʃN���X.
*/
class Ground : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	Ground(string name) : 
		IGameObject(name)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~Ground()
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