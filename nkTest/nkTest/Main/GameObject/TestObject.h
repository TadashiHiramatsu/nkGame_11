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

private:

	/** モデルクラス. */
	ModelRender Model_;

};