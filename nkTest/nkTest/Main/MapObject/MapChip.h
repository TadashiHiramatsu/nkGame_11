/**
* �}�b�v�`�b�v�N���X�̒�`.
*/
#pragma once

/**
* �}�b�v�`�b�v�N���X.
*/
class MapChip : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	MapChip()
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~MapChip()
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