/**
* ボックス形状クラスの定義.
*/
#pragma once

#include"nkShape.h"

namespace nkEngine
{

	/**
	* ボックス形状クラス.
	*/
	class BoxShape : public IShape
	{
	public:

		/**
		* コンストラクタ.
		*/
		BoxShape(IGameObject* go) : 
			IShape(go)
		{
		}

		/**
		* デストラクタ.
		*/
		~BoxShape()
		{
		}

	private:

		/**
		* バッファの作成.
		*/
		void CreateBuffer()override;

	};

}