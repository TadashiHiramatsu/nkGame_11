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