/**
* �f�o�b�O�E�B���h�E�Ǘ��N���X�̒�`.
*/
#pragma once

#include"nkDebugWindow.h"

namespace nkEngine
{

	/**
	* �f�o�b�O�E�B���h�E�Ǘ��N���X.
	*/
	class DebugWindowManager : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		DebugWindowManager()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~DebugWindowManager()
		{
		}

		/**
		* ������.
		*/
		void Start(void* hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);

		/**
		* �X�V.
		*/
		void Update();

		/**
		* �`��.
		*/
		void Render();

		/**
		* ���.
		*/
		void Release();

		/**
		* �f�o�b�O�E�B���h�E��ǉ�.
		*/
		template <class TDW>
		IDebugWindow* AddDebugWindow()
		{
#ifdef DEBUG
			//�쐬.
			TDW* debugWindow = new TDW();
			//������.
			debugWindow->Start();
			//�o�^.
			DebugWindowList_.push_back(debugWindow);
			//�Ԃ�.
			return debugWindow;
#endif
			return nullptr;
		}

		/**
		* �f�o�b�O�E�B���h�E���擾.
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
		* �v���V�[�W��.
		*/
		static IMGUI_API LRESULT Proc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:

#ifdef DEBUG

		/** �f�o�b�O�E�B���h���X�g, */
		list<IDebugWindow*> DebugWindowList_;
#endif

	};

}

#ifdef DEBUG
extern IMGUI_API LRESULT   ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif