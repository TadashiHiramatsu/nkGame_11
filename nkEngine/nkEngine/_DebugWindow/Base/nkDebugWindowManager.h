/**
* デバッグウィンドウ管理クラスの定義.
*/
#pragma once

#include"nkDebugWindow.h"

namespace nkEngine
{

	/**
	* デバッグウィンドウ管理クラス.
	*/
	class DebugWindowManager : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		DebugWindowManager()
		{
		}

		/**
		* デストラクタ.
		*/
		~DebugWindowManager()
		{
		}

		/**
		* 初期化.
		*/
		void Start(void* hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);

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
		* デバッグウィンドウを追加.
		*/
		template <class TDW>
		IDebugWindow* AddDebugWindow()
		{
#ifdef DEBUG
			//作成.
			TDW* debugWindow = new TDW();
			//初期化.
			debugWindow->Start();
			//登録.
			DebugWindowList_.push_back(debugWindow);
			//返す.
			return debugWindow;
#endif
			return nullptr;
		}

		/**
		* デバッグウィンドウを取得.
		*/
		IDebugWindow* GetDebugWindow(string name)
		{
#ifdef DEBUG
			auto& it = find_if(DebugWindowList_.begin(), DebugWindowList_.end(), [name](IDebugWindow* dw) {return dw->GetName() == name; });
		
			if (it != DebugWindowList_.end())
			{
				return (*it);
			}
#endif
			return nullptr;
		}

		/**
		* プロシージャ.
		*/
		static IMGUI_API LRESULT Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:

#ifdef DEBUG

		/** デバッグウィンドリスト, */
		list<IDebugWindow*> DebugWindowList_;
#endif

	};

}

#ifdef DEBUG
extern IMGUI_API LRESULT   ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif