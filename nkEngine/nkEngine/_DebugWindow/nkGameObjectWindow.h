/**
* ゲームオブジェクト表示ウィンドウクラスの定義.
*/
#pragma once

#include"Base\nkDebugWindow.h"

namespace nkEngine
{

	/**
	* ゲームオブジェクト表示ウィンドウクラス.
	*/
	class GameObjectWindow : public IDebugWindow
	{
	public:

		/**
		* コンストラクタ.
		*/
		GameObjectWindow()
		{
		}

		/**
		* デストラクタ.
		*/
		~GameObjectWindow()
		{
		}

		/**
		* 描画.
		*/
		void Render()override;

	private:

	};
}