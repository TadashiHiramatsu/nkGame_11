/**
* メインライトクラスの定義.
*/
#pragma once

/**
* メインライトクラス.
*/
class MainLight : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	MainLight(string name) : 
		IGameObject(name)
	{
	}

	/**
	* デストラクタ.
	*/
	~MainLight()
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
	* ライトを取得.
	*/
	Light& GetLight()
	{
		return Light_;
	}

private:

	/** ライトクラス. */
	Light Light_;

};
