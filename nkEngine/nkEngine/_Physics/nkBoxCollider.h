/**
 * ボックスコライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * ボックスコライダークラス.
	 */
	class BoxCollider : public ICollider
	{
	public:

		/**
		 * コンストラクタ.
		 */
		BoxCollider()
		{
		}

		/**
		 * デストラクタ.
		 */
		~BoxCollider()
		{
		}

		/**
		 * ボックスコライダー作成.
		 *
		 * @param size	サイズ.
		 */
		void Create(const Vector3& size);

		/**
		* 解放.
		*/
		void Release()override
		{
		}

	};

}