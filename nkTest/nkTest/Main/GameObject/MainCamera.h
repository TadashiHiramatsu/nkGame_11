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
	MainCamera()
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
	Camera* GetCamera()
	{
		return &Camera_;
	}

	/**
	* 前方向を取得.
	*/
	const Vector3& GetFront()
	{
		Vector3 front;
		front.Sub(Camera_.GetTarget(), Camera_.GetPosition());
		front.Normalize();
		return front;
	}

private:

	/** カメラクラス. */
	Camera Camera_;

	/** カメラの距離. */
	float Distance_ = 10;

};

/** グローバル. */
extern MainCamera* g_MainCamera;