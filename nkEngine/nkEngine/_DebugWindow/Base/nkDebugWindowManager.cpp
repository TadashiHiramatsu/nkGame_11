/**
* デバッグウィンドウ管理クラスの実装.
*/
#include"nkstdafx.h"
#include"nkDebugWindowManager.h"

namespace nkEngine
{

	/**
	* 初期化.
	*/
	void DebugWindowManager::Start(void * hwnd, ID3D11Device * device, ID3D11DeviceContext * device_context)
	{
#ifdef DEBUG
		//Imguiの初期化.
		ImGui_ImplDX11_Init(hwnd, device, device_context);
#endif
	}

	/**
	* 更新.
	*/
	void DebugWindowManager::Update()
	{
#ifdef DEBUG
		ImGui_ImplDX11_NewFrame();
#endif
	}

	/**
	* 描画.
	*/
	void DebugWindowManager::Render()
	{
#ifdef DEBUG
		for (auto it : DebugWindowList_)
		{
			it->RenderWrapper();
		}
		ImGui::Render();
#endif
	}

	/**
	* 解放.
	*/
	void DebugWindowManager::Release()
	{
#ifdef DEBUG
		//Imguiの解放.
		ImGui_ImplDX11_Shutdown();
#endif
	}

	/**
	* プロシージャ.
	*/
	LRESULT DebugWindowManager::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
#ifdef DEBUG
		return ImGui_ImplDX11_WndProcHandler(hWnd, msg, wParam, lParam);
#endif
		return S_OK;
	}

}