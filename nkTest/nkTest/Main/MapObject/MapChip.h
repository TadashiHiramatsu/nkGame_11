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
	MapChip(string name) :
		IGameObject(name)
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

private:

	BoxCollider Collider_;
	RigidBody RigidBody_;

};