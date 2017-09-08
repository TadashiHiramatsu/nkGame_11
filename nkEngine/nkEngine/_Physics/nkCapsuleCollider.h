/**
 * カプセルコライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * カプセルコライダー.
	 */
	class CapsuleCollider : public ICollider
	{
	public:

		/**
		 * コンストラクタ.
		 */
		CapsuleCollider()
		{
		}

		/**
		 * デストラクタ.
		 */
		~CapsuleCollider()
		{
		}

		/**
		 * カプセルコライダー作成.
		 *
		 * @param radius	半径.
		 * @param height	高さ.
		 */
		void Create(const float radius, const float height);

		/**
		* 解放.
		*/
		void Release()override
		{
		}

	};

}