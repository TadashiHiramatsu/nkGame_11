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

private:

	MeshCollider Collider_;
	RigidBody RigidBody_;


};