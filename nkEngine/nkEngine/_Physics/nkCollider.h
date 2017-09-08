/**
* コライダークラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	 * コライダーの基底クラス.
	 * 剛体の使用するコライダーはこのクラスを継承し作成する.
	 */
	class ICollider : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		ICollider()
		{
		}

		/**
		* デストラクタ.
		*/
		virtual ~ICollider()
		{
			Release();
		}

		/**
		 * ボディの取得.
		 */
		btCollisionShape* GetBody()
		{
			return Shape_;
		}

		/**
		* 解放.
		*/
		virtual void Release()
		{
			if (Shape_)
			{
				delete Shape_;
				Shape_ = nullptr;
			}
		}

	protected:

		/** 形状. */
		btCollisionShape* Shape_ = nullptr;

	};

}