/**
* テストFBXオブジェクトクラスの定義.
*/
#pragma once

/**
* テストFBXオブジェクトクラスの.
*/
class UnityChan : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	UnityChan(string name) :
		IGameObject(name)
	{
	}

	/**
	* デストラクタ.
	*/
	~UnityChan()
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
	* Render前の描画.
	*/
	void PreRender()override;

	/**
	* 描画.
	*/
	void Render()override;

private:

	/** モデル描画クラス. */
	ModelRender ModelRender_;

};