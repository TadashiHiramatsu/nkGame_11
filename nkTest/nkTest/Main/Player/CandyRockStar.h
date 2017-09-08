/**
* CandyRockStarクラスの定義.
*/
#pragma once

/**
* CandyRockStarクラス.
*/
class CandyRockStar : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	CandyRockStar(string name) :
		IGameObject(name)
	{
	}

	/**
	* デストラクタ.
	*/
	~CandyRockStar()
	{
	}

	/**
	* 初期化.
	*/
	void Start()override;

	/**
	* 更新.
	*/
	void Update()override;

};