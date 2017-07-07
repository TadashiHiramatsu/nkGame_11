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
	MapChip()
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