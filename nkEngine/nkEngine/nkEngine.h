/**
* エンジンクラスの定義.
*/
#pragma once

#include"nkMainLoop.h"

#include"_Graphics\3DObject\Model\nkModelManager.h"
#include"_Physics\nkPhysics.h"

namespace nkEngine
{
	/** レンダリングコンテキスト. */
	class RenderContext;

	/**
	* エンジン初期化用パラメータ.
	*/
	struct InitParamS
	{
	public:

		/** インスタンスハンドル. */
		HINSTANCE hInstance_ = nullptr;
		/** スクリーンの横幅. */
		int ScreenBufferW_ = 1200;
		/** スクリーンの高さ. */
		int ScreenBufferH_ = 675;
		/** 内部解像度の横幅. */
		int FrameBufferW_ = 1200;
		/** 内部解像度の高さ. */
		int FrameBufferH_ = 675;
		/** ゲームの表示名. */
		string GameName_ = "Game";
	};

	/**
	* エンジンクラス.
	* シングルトンクラス.
	*/
	class EngineSingleton : Noncopyable
	{
	private:

		/**
		* コンストラクタ.
		*/
		EngineSingleton()
		{
		}

		/**
		* デストラクタ.
		*/
		~EngineSingleton()
		{
		}

	public:

		/**
		* インスタンスの取得.
		*/
		static EngineSingleton& GetInstance()
		{
			static EngineSingleton instance;
			return instance;
		}

		/**
		* エンジンの初期化.
		*
		* @param initParam	初期化パラメータ.
		*/
		bool Init(const InitParamS& initParam);

		/**
		* メインループの実行.
		*/
		void RunMainLoop();

		/**
		* D3D11デバイスの取得.
		*/
		ID3D11Device* GetDevice()
		{
			return D3DDevice_;
		}

		/**
		* レンダリングコンテキストの取得.
		*/
		RenderContext& GetRenderContext()
		{
			return RenderContext_;
		}

		/**
		* スワップチェインの取得.
		*/
		IDXGISwapChain* GetSwapChain()
		{
			return D3DSwapChain_;
		}

		/**
		* フレームの幅を取得.
		*
		* @return	The frame w.
		*/
		int GetFrameW() const
		{
			return FrameBufferW_;
		}

		/**
		* フレームの高さを取得.
		*
		* @return	The frame h.
		*/
		int GetFrameH() const
		{
			return FrameBufferH_;
		}

		/**
		* スクリーンの幅を取得.
		*
		* @return	The screen w.
		*/
		int GetScreenW() const
		{
			return ScreenBufferW_;
		}

		/**
		* スクリーンの高さを取得.
		*
		* @return	The screen h.
		*/
		int GetScreenH() const
		{
			return ScreenBufferH_;
		}

		HWND GetHWND() const
		{
			return hWnd_;
		}

		/**
		* シャドウマップクラスを取得.
		*/
		ShadowMap& GetShadowMap()
		{
			return MainLoop_.ShadowMap_;
		}

		/**
		* モデル管理クラスを取得.
		*/
		ModelManager& GetModelManager()
		{
			return ModelManager_;
		}

		/**
		* デバッグウィンドウ管理クラスを取得.
		*/
		DebugWindowManager& GetDebugWindowManager()
		{
			return DebugWindowManager_;
		}

		/**
		* 物理クラスを取得.
		*/
		Physics& GetPhysics()
		{
			return Physics_;
		}

	private:

		/**
		* ウィンドウの初期化.
		*
		* @param initParam	初期化パラメータ.
		*/
		bool InitWindow(const InitParamS& initParam);

		/**
		* DirectX11の初期化.
		*
		* @param initParam	初期化パラメータ.
		*/
		bool InitDirectX(const InitParamS& initParam);

		/**
		* 終了処理.
		*/
		void Final();

		/**
		* ウィンドウプロシージャ.
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:

		/** アプリケーションのインスタンス. */
		HINSTANCE hInstance_ = nullptr;
		/** ウィンドウハンドル. */
		HWND hWnd_ = nullptr;
		
		/** ドライバの種類のオプション. */
		D3D_DRIVER_TYPE D3DDriverType_ = D3D_DRIVER_TYPE_NULL;
		/** Direct3Dデバイスのターゲットとなる機能セット. */
		D3D_FEATURE_LEVEL D3DFeatureLevel_ = D3D_FEATURE_LEVEL_11_0;
		/** D3D11デバイス. */
		ID3D11Device* D3DDevice_ = nullptr;
		/** レンダリングコンテキスト. */
		RenderContext RenderContext_;
		/** D3D11即時デバイスコンテキスト. */
		ID3D11DeviceContext* D3DImmediateContext_ = nullptr;
		/** スワップチェイン. */
		IDXGISwapChain* D3DSwapChain_ = nullptr;

		/** メインループクラス. */
		MainLoop MainLoop_;

		/** モデル管理クラス. */
		ModelManager ModelManager_;

		/** 物理クラス. */
		Physics Physics_;
		
		/** フレームバッファの幅.内部解像度. */
		int FrameBufferW_ = 0;
		/** フレームバッファの高さ.内部解像度. */
		int FrameBufferH_ = 0;
		/** スクリーンバッファの幅. */
		int ScreenBufferW_ = 0;
		/** スクリーンバッファの高さ. */
		int ScreenBufferH_ = 0;

		/** デバッグウィンドウ管理クラス. */
		DebugWindowManager DebugWindowManager_;
	
	};

	/**
	* エンジンを取得.
	*/
	static EngineSingleton& Engine()
	{
		return EngineSingleton::GetInstance();
	}

}
