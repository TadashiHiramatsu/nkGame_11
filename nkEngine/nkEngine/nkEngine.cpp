/**
* エンジンクラスの実装.
*/
#include"nkstdafx.h"
#include"nkEngine.h"

#include"_DebugWindow\nkFPSWindow.h"
#include"_DebugWindow\nkGameObjectWindow.h"

namespace nkEngine
{

	/**
	* エンジンの初期化.
	*
	* @param initParam	初期化パラメータ.
	*/
	bool EngineSingleton::Init(const InitParamS & initParam)
	{
		//ウィンドウの初期化.
		if (!InitWindow(initParam))
		{
			NK_ASSERT(false, "Window初期化できねぇ.");
			return false;
		}

		//Direct3D11の初期化.
		if (!InitDirectX(initParam))
		{
			NK_ASSERT(false, "DirectX初期化できねぇ.");
			return false;
		}

		if (!MainLoop_.Init())
		{
			NK_ASSERT(false, "色々初期化できねぇ.");
			return false;
		}

		Input().Init(true, true);

		//モデル管理クラスを初期化.
		ModelManager_.Init();

		GameObjectManager().StartGOM(10);

		//デバッグウィンドウ管理クラスの初期化.
		DebugWindowManager_.Start(hWnd_, D3DDevice_, D3DImmediateContext_);

		//FPS表示ウィンドウクラスを追加.
		DebugWindowManager_.AddDebugWindow<FPSWindow>();
		//ゲームオブジェクト表示ウィンドウクラスを追加.
		DebugWindowManager_.AddDebugWindow<GameObjectWindow>();

		return true;
	}

	/**
	* メインループの実行.
	*/
	void EngineSingleton::RunMainLoop()
	{
		MSG msg = { 0 };
		while (WM_QUIT != msg.message)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//更新.
				MainLoop_.Update();
				//描画.
				MainLoop_.Render();
			}
		}
	}


	/**
	* ウィンドウの初期化.
	*
	* @param initParam	初期化パラメータ.
	*/
	bool EngineSingleton::InitWindow(const InitParamS & initParam)
	{
		//スクリーンサイズ.
		ScreenBufferW_ = initParam.ScreenBufferW_;
		ScreenBufferH_ = initParam.ScreenBufferH_;

		WNDCLASSEX wc =
		{
			sizeof(WNDCLASSEX),
			CS_CLASSDC,
			MsgProc,
			0L, 0L,
			GetModuleHandle(nullptr),
			nullptr,
			LoadCursor(NULL, IDC_ARROW),
			nullptr,
			nullptr,
			TEXT("nkGame"),
			nullptr
		};
		RegisterClassEx(&wc);

		RECT rd;
		HWND hDeskWnd = GetDesktopWindow();
		GetWindowRect(hDeskWnd, &rd);

		//ウィンドウ作成
		hWnd_ = CreateWindow(
			TEXT("nkGame"),
			(LPCSTR)initParam.GameName_.c_str(),
			WS_SYSMENU | WS_MINIMIZEBOX,
			(rd.right - ScreenBufferW_) / 2,
			(rd.bottom - ScreenBufferH_) / 2,
			ScreenBufferW_,
			ScreenBufferH_,
			nullptr,
			nullptr,
			wc.hInstance,
			nullptr
		);

		RECT rw, cw;
		GetWindowRect(hWnd_, &rw);
		GetClientRect(hWnd_, &cw);

		//ウィンドウの初期位置計算
		int new_width = (rw.right - rw.left) - (cw.right - cw.left) + ScreenBufferW_;
		int new_height = (rw.bottom - rw.top) - (cw.bottom - cw.top) + ScreenBufferH_;

		//スクリーン座標（0,0）にウィンドウを初期配置
		SetWindowPos(hWnd_, NULL, (rd.right - new_width) / 2, 0, new_width, new_height, SWP_SHOWWINDOW);

		ShowWindow(hWnd_, SW_SHOWDEFAULT);

		return hWnd_ != nullptr;
	}

	/**
	* DirectX11の初期化.
	*
	* @param initParam	初期化パラメータ.
	*/
	bool EngineSingleton::InitDirectX(const InitParamS & initParam)
	{
		UINT createDeviceFlags = 0;

#ifdef DEBUG //デバック.
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,	//ハードウェアドライバー。Direct3D機能をハードウェアに実装します.
			D3D_DRIVER_TYPE_WARP,		//WARPドライバー。高パフォーマンスのソフトウェアラスタライザー.
			D3D_DRIVER_TYPE_REFERENCE,	//リファレンスドライバー。すべてのDirect3D機能をサポートするソフトウェア実装.
		};

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,	//シェーダーモデル5などのDirect3D 11.0でサポートされている機能.
			D3D_FEATURE_LEVEL_10_1, //シェーダーモデル4などのDirect3D 10.1でサポートされている機能.
			D3D_FEATURE_LEVEL_10_0, //シェーダーモデル4などのDirect3D 10.0でサポートされている機能.
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		//フレームサイズ.
		FrameBufferW_ = initParam.FrameBufferW_;
		FrameBufferH_ = initParam.FrameBufferH_;

		//スワップチェインを作成.
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		
		//描画先の縦横サイズ、フォーマット(形式)を設定.
		sd.BufferCount = 1; //スワップチェインのバッファ数。通常は１.
		sd.BufferDesc.Width = FrameBufferW_;  //フレームバッファの幅.
		sd.BufferDesc.Height = FrameBufferH_; //フレームバッファの高さ.
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//フレームバッファのフォーマット。R8G8B8A8の32bit。
		
		//描画先の更新頻度(60fpsだったり30fpsだったりというあれ)を分数形式で設定.
		sd.BufferDesc.RefreshRate.Numerator = 60; //モニタのリフレッシュレート.
		sd.BufferDesc.RefreshRate.Denominator = 1; //分母。リフレッシュレートが割られる.
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //サーフェスまたはリソースを出力レンダリングターゲットとして使用.
		
		//他、描画先の使用方法(まあここではDXGI_USAGE_RENDER_TARGET_OUTPUTだろう)、描画先ウィンドウのハンドル、ウィンドウモードか否か、MSAAのクオリティやカウント等を設定.
		sd.SampleDesc.Count = 1; //ピクセル単位のマルチサンプリングの数.MSAAはなし.
		sd.SampleDesc.Quality = 0; //MSAAなし.
		sd.Windowed = TRUE;	//ウィンドウモード.
		sd.OutputWindow = hWnd_; //描画するウィンドウハンドルってことかな.

		//全てのドライバタイプでスワップチェインの作成を試す.
		HRESULT hr = E_FAIL;
		for(auto& driverType : driverTypes)
		{
			//ドライバタイプを設定.
			D3DDriverType_ = driverType;
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr, //どのビデオアダプタを使用するか？既定ならばnullptrで、IDXGIAdapterのアドレス.
				D3DDriverType_, //ドライバのタイプ.
				nullptr, //上記をD3D_DRIVER_TYPE_SOFTWAREに設定した際に、その処理を行うDLLのハンドルを渡す。それ以外を指定している際には必ずnullptrを渡す.
				createDeviceFlags, //何らかのフラグを指定する。D3D11_CREATE_DEVICE列挙型.
				featureLevels, //D3D_FEATURE_LEVEL列挙型の配列.
				numFeatureLevels, //上記配列の数.
				D3D11_SDK_VERSION, //SDKのバージョン。必ずこの値.
				&sd, //スワップチェインの設定.
				&D3DSwapChain_, //スワップチェイン.
				&D3DDevice_, //D3D11デバイス.
				&D3DFeatureLevel_, //Direct3Dデバイスのターゲットとなる機能セット.
				&D3DImmediateContext_); //デバイスコンテキスト.

			if (SUCCEEDED(hr))
			{
				//スワップチェインを作成できたのでループを抜ける.
				break;
			}
		}
		if (FAILED(hr))
		{
			//スワップチェインを作成出来なかった.
			return false;
		}

		//レンダリングコンテキストの初期化。
		RenderContext_.Init(D3DImmediateContext_);

		return true;
	}

	/**
	* 終了処理.
	*/
	void EngineSingleton::Final()
	{
		MainLoop_.Release();

		//モデル管理クラスを解放.
		ModelManager_.Release();

		//デバッグウィンドウ管理クラスの解放.
		DebugWindowManager_.Release();

		if (D3DImmediateContext_)
		{
			D3DImmediateContext_->ClearState();
		}
		if (D3DSwapChain_)
		{
			D3DSwapChain_->Release();
		}
		if (D3DImmediateContext_)
		{
			D3DImmediateContext_->Release();
		}
		if (D3DDevice_)
		{
			D3DDevice_->Release();
		}
	}

	/**
	* ウィンドウプロシージャ.
	*/
	LRESULT EngineSingleton::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
#ifdef DEBUG
		//マウスで動くようにする.
		if (DebugWindowManager::Proc(hWnd, msg, wParam, lParam))
		{
			return true;
		}
#endif

		switch (msg)
		{
		case WM_KEYDOWN: // キーを押したとき
			switch (wParam)
			{
			case VK_ESCAPE: // エスケープキー
				GetInstance().Final();
				PostQuitMessage(0);
				return 0;
			}
			break;
		case WM_DESTROY: // 削除.
			GetInstance().Final();
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return 0L;
	}

}