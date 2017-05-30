/**
* メインループクラスの定義.
*/
#pragma once

#include"_Graphics\nkRenderTarget.h"

#include"_Graphics\PreRender\nkShadowMap.h"

namespace nkEngine
{

	/**
	* メインループクラス.
	*/
	class MainLoop : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		MainLoop()
		{
		}

		/**
		* デストラクタ.
		*/
		~MainLoop()
		{
		}

		/**
		* 初期化.
		*/
		bool Init();

		/**
		* 更新.
		*/
		void Update();

		/**
		* 描画.
		*/
		void Render();

		/**
		* 解放.
		*/
		void Release();

		/**
		* メインレンダリングターゲットを切り替え.
		*/
		void ToggleMainRenderTarget()
		{
			CurrentMainRenderTarget_ ^= 1;
		}

		/**
		* メインレンダリングターゲットを取得.
		*/
		RenderTarget& GetMainRenderTarget()
		{
			return MainRenderTarget_[CurrentMainRenderTarget_];
		}

	private:

		/**
		* メインレンダリングターゲットの内容をバックバッファにコピー.
		*/
		void CopyMainRenderTargetToBackBuffer();

	private:

		/** 選択中のメインレンダリングターゲット. */
		int CurrentMainRenderTarget_ = 0;
		/** メインレンダリングターゲット. */
		RenderTarget MainRenderTarget_[2];

	public:

		/** シャドウマップクラス. */
		ShadowMap ShadowMap_;

	};

}