/**
* マップチップクラスの定義.
*/
#pragma once

/**
* マップチップクラス.
*/
class MapChip : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	MapChip(string name) :
		IGameObject(name)
	{
	}

	/**
	* デストラクタ.
	*/
	~MapChip()
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

private:

	BoxCollider Collider_;
	RigidBody RigidBody_;

};