/**
* �f�o�b�O�E�B���h�E�Ǘ��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkDebugWindowManager.h"

namespace nkEngine
{

	/**
	* ������.
	*/
	void DebugWindowManager::Start(void * hwnd, ID3D11Device * device, ID3D11DeviceContext * device_context)
	{
#ifdef DEBUG
		//Imgui�̏�����.
		ImGui_ImplDX11_Init(hwnd, device, device_context);
#endif
	}

	/**
	* �X�V.
	*/
	void DebugWindowManager::Update()
	{
#ifdef DEBUG
		ImGui_ImplDX11_NewFrame();
#endif
	}

	/**
	* �`��.
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
	* ���.
	*/
	void DebugWindowManager::Release()
	{
#ifdef DEBUG
		//Imgui�̉��.
		ImGui_ImplDX11_Shutdown();
#endif
	}

	/**
	* �v���V�[�W��.
	*/
	LRESULT DebugWindowManager::Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
#ifdef DEBUG
		return ImGui_ImplDX11_WndProcHandler(hWnd, msg, wParam, lParam);
#endif
		return S_OK;
	}

}