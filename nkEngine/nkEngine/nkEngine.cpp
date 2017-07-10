/**
* �G���W���N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkEngine.h"

#include"_DebugWindow\nkFPSWindow.h"
#include"_DebugWindow\nkGameObjectWindow.h"

namespace nkEngine
{

	/**
	* �G���W���̏�����.
	*
	* @param initParam	�������p�����[�^.
	*/
	bool EngineSingleton::Init(const InitParamS & initParam)
	{
		//�E�B���h�E�̏�����.
		if (!InitWindow(initParam))
		{
			NK_ASSERT(false, "Window�������ł��˂�.");
			return false;
		}

		//Direct3D11�̏�����.
		if (!InitDirectX(initParam))
		{
			NK_ASSERT(false, "DirectX�������ł��˂�.");
			return false;
		}

		if (!MainLoop_.Init())
		{
			NK_ASSERT(false, "�F�X�������ł��˂�.");
			return false;
		}

		Input().Init(true, true);

		//���f���Ǘ��N���X��������.
		ModelManager_.Init();

		GameObjectManager().StartGOM(10);

		//�f�o�b�O�E�B���h�E�Ǘ��N���X�̏�����.
		DebugWindowManager_.Start(hWnd_, D3DDevice_, D3DImmediateContext_);

		//FPS�\���E�B���h�E�N���X��ǉ�.
		DebugWindowManager_.AddDebugWindow<FPSWindow>();
		//�Q�[���I�u�W�F�N�g�\���E�B���h�E�N���X��ǉ�.
		DebugWindowManager_.AddDebugWindow<GameObjectWindow>();

		return true;
	}

	/**
	* ���C�����[�v�̎��s.
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
				//�X�V.
				MainLoop_.Update();
				//�`��.
				MainLoop_.Render();
			}
		}
	}


	/**
	* �E�B���h�E�̏�����.
	*
	* @param initParam	�������p�����[�^.
	*/
	bool EngineSingleton::InitWindow(const InitParamS & initParam)
	{
		//�X�N���[���T�C�Y.
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

		//�E�B���h�E�쐬
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

		//�E�B���h�E�̏����ʒu�v�Z
		int new_width = (rw.right - rw.left) - (cw.right - cw.left) + ScreenBufferW_;
		int new_height = (rw.bottom - rw.top) - (cw.bottom - cw.top) + ScreenBufferH_;

		//�X�N���[�����W�i0,0�j�ɃE�B���h�E�������z�u
		SetWindowPos(hWnd_, NULL, (rd.right - new_width) / 2, 0, new_width, new_height, SWP_SHOWWINDOW);

		ShowWindow(hWnd_, SW_SHOWDEFAULT);

		return hWnd_ != nullptr;
	}

	/**
	* DirectX11�̏�����.
	*
	* @param initParam	�������p�����[�^.
	*/
	bool EngineSingleton::InitDirectX(const InitParamS & initParam)
	{
		UINT createDeviceFlags = 0;

#ifdef DEBUG //�f�o�b�N.
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,	//�n�[�h�E�F�A�h���C�o�[�BDirect3D�@�\���n�[�h�E�F�A�Ɏ������܂�.
			D3D_DRIVER_TYPE_WARP,		//WARP�h���C�o�[�B���p�t�H�[�}���X�̃\�t�g�E�F�A���X�^���C�U�[.
			D3D_DRIVER_TYPE_REFERENCE,	//���t�@�����X�h���C�o�[�B���ׂĂ�Direct3D�@�\���T�|�[�g����\�t�g�E�F�A����.
		};

		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,	//�V�F�[�_�[���f��5�Ȃǂ�Direct3D 11.0�ŃT�|�[�g����Ă���@�\.
			D3D_FEATURE_LEVEL_10_1, //�V�F�[�_�[���f��4�Ȃǂ�Direct3D 10.1�ŃT�|�[�g����Ă���@�\.
			D3D_FEATURE_LEVEL_10_0, //�V�F�[�_�[���f��4�Ȃǂ�Direct3D 10.0�ŃT�|�[�g����Ă���@�\.
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		//�t���[���T�C�Y.
		FrameBufferW_ = initParam.FrameBufferW_;
		FrameBufferH_ = initParam.FrameBufferH_;

		//�X���b�v�`�F�C�����쐬.
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		
		//�`���̏c���T�C�Y�A�t�H�[�}�b�g(�`��)��ݒ�.
		sd.BufferCount = 1; //�X���b�v�`�F�C���̃o�b�t�@���B�ʏ�͂P.
		sd.BufferDesc.Width = FrameBufferW_;  //�t���[���o�b�t�@�̕�.
		sd.BufferDesc.Height = FrameBufferH_; //�t���[���o�b�t�@�̍���.
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�t���[���o�b�t�@�̃t�H�[�}�b�g�BR8G8B8A8��32bit�B
		
		//�`���̍X�V�p�x(60fps��������30fps��������Ƃ�������)�𕪐��`���Őݒ�.
		sd.BufferDesc.RefreshRate.Numerator = 60; //���j�^�̃��t���b�V�����[�g.
		sd.BufferDesc.RefreshRate.Denominator = 1; //����B���t���b�V�����[�g��������.
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //�T�[�t�F�X�܂��̓��\�[�X���o�̓����_�����O�^�[�Q�b�g�Ƃ��Ďg�p.
		
		//���A�`���̎g�p���@(�܂������ł�DXGI_USAGE_RENDER_TARGET_OUTPUT���낤)�A�`���E�B���h�E�̃n���h���A�E�B���h�E���[�h���ۂ��AMSAA�̃N�I���e�B��J�E���g����ݒ�.
		sd.SampleDesc.Count = 1; //�s�N�Z���P�ʂ̃}���`�T���v�����O�̐�.MSAA�͂Ȃ�.
		sd.SampleDesc.Quality = 0; //MSAA�Ȃ�.
		sd.Windowed = TRUE;	//�E�B���h�E���[�h.
		sd.OutputWindow = hWnd_; //�`�悷��E�B���h�E�n���h�����Ă��Ƃ���.

		//�S�Ẵh���C�o�^�C�v�ŃX���b�v�`�F�C���̍쐬������.
		HRESULT hr = E_FAIL;
		for(auto& driverType : driverTypes)
		{
			//�h���C�o�^�C�v��ݒ�.
			D3DDriverType_ = driverType;
			hr = D3D11CreateDeviceAndSwapChain(
				nullptr, //�ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr�ŁAIDXGIAdapter�̃A�h���X.
				D3DDriverType_, //�h���C�o�̃^�C�v.
				nullptr, //��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n��.
				createDeviceFlags, //���炩�̃t���O���w�肷��BD3D11_CREATE_DEVICE�񋓌^.
				featureLevels, //D3D_FEATURE_LEVEL�񋓌^�̔z��.
				numFeatureLevels, //��L�z��̐�.
				D3D11_SDK_VERSION, //SDK�̃o�[�W�����B�K�����̒l.
				&sd, //�X���b�v�`�F�C���̐ݒ�.
				&D3DSwapChain_, //�X���b�v�`�F�C��.
				&D3DDevice_, //D3D11�f�o�C�X.
				&D3DFeatureLevel_, //Direct3D�f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g.
				&D3DImmediateContext_); //�f�o�C�X�R���e�L�X�g.

			if (SUCCEEDED(hr))
			{
				//�X���b�v�`�F�C�����쐬�ł����̂Ń��[�v�𔲂���.
				break;
			}
		}
		if (FAILED(hr))
		{
			//�X���b�v�`�F�C�����쐬�o���Ȃ�����.
			return false;
		}

		//�����_�����O�R���e�L�X�g�̏������B
		RenderContext_.Init(D3DImmediateContext_);

		return true;
	}

	/**
	* �I������.
	*/
	void EngineSingleton::Final()
	{
		MainLoop_.Release();

		//���f���Ǘ��N���X�����.
		ModelManager_.Release();

		//�f�o�b�O�E�B���h�E�Ǘ��N���X�̉��.
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
	* �E�B���h�E�v���V�[�W��.
	*/
	LRESULT EngineSingleton::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
#ifdef DEBUG
		//�}�E�X�œ����悤�ɂ���.
		if (DebugWindowManager::Proc(hWnd, msg, wParam, lParam))
		{
			return true;
		}
#endif

		switch (msg)
		{
		case WM_KEYDOWN: // �L�[���������Ƃ�
			switch (wParam)
			{
			case VK_ESCAPE: // �G�X�P�[�v�L�[
				GetInstance().Final();
				PostQuitMessage(0);
				return 0;
			}
			break;
		case WM_DESTROY: // �폜.
			GetInstance().Final();
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		return 0L;
	}

}