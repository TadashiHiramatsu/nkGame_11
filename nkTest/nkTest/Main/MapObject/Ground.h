/**
* 地面クラスの定義.
*/
#pragma once

/**
* 地面クラス.
*/
class Ground : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	Ground(string name) : 
		IGameObject(name)
	{
	}

	/**
	* デストラクタ.
	*/
	~Ground()
	{
	}

	/**
	* 初期化.
	*/
	void Start()override;

private:

	MeshCollider Collider_;
	RigidBody RigidBody_;


};