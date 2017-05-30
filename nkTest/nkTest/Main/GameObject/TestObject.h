/**
* テストオブジェクトクラスの定義.
*/
#pragma once

class TestObject : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	TestObject()
	{
	}

	/**
	* デストラクタ.
	*/
	~TestObject()
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

	/**
	* 描画.
	*/
	void Render()override;

	void SetParent(Transform* p)
	{
		Transform_.Parent_ = p;
	}

private:

	/** ライトクラス. */
	Light Light_;

	/** ボックス形状. */
	BoxShape Box_;

};