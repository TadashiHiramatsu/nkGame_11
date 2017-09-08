/**
* メインカメラクラスの定義.
*/
#pragma once

/**
* メインカメラクラス.
*/
class MainCamera : public IGameObject
{
public:

	/**
	* コンストラクタ.
	*/
	MainCamera(string name) : 
		IGameObject(name)
	{
	}

	/**
	* デストラクタ.
	*/
	~MainCamera()
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
	* カメラを取得.
	*
	* @return	カメラクラス.
	*/
	Camera& GetCamera()
	{
		return Camera_;
	}

private:

	/**
	* デバック状態の更新.
	*/
	void DebugUpdate();

private:

	/** カメラクラス. */
	Camera Camera_;

	/** カメラの距離. */
	float Distance_ = 10;

};
