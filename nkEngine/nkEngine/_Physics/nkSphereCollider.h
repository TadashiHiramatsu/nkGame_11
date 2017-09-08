/**
 * 球体コライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * 球体コライダークラス.
	 */
	class SphereCollider : public ICollider
	{
	public:

		/**
		 * コンストラクタ.
		 */
		SphereCollider()
		{
		}

		/**
		 * デストラクタ.
		 */
		~SphereCollider()
		{
		}

		/**
		 * 球体コライダー作成.
		 *
		 * @param radius	半径.
		 */
		void Create(const float radius);

		/**
		* 解放.
		*/
		void Release()override
		{
		}
	
	};

}