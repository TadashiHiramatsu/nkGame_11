/**
* FPS表示ウィンドウクラスの定義.
*/
#pragma once

#include"Base\nkDebugWindow.h"

namespace nkEngine
{
	
	/**
	* FPS表示ウィンドウクラス.
	*/
	class FPSWindow : public IDebugWindow
	{
	public:

		/**
		* コンストラクタ.
		*/
		FPSWindow()
		{
		}

		/**
		* デストラクタ.
		*/
		~FPSWindow()
		{
		}

		/**
		* 初期化.
		*/
		void Start()override;

		/**
		* 描画.
		*/
		void Render()override;

	private:

		/** FPSリスト. */
		vector<float> FPSList_;

	};

}