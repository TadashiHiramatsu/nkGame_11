/**
* CandyRockStar�N���X�̒�`.
*/
#pragma once

/**
* CandyRockStar�N���X.
*/
class CandyRockStar : public IGameObject
{
public:

	/**
	* �R���X�g���N�^.
	*/
	CandyRockStar(string name) :
		IGameObject(name)
	{
	}

	/**
	* �f�X�g���N�^.
	*/
	~CandyRockStar()
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

};