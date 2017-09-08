/**
* �G���W���N���X�̒�`.
*/
#pragma once

#include"nkMainLoop.h"

#include"_Graphics\3DObject\Model\nkModelManager.h"
#include"_Physics\nkPhysics.h"

namespace nkEngine
{
	/** �����_�����O�R���e�L�X�g. */
	class RenderContext;

	/**
	* �G���W���������p�p�����[�^.
	*/
	struct InitParamS
	{
	public:

		/** �C���X�^���X�n���h��. */
		HINSTANCE hInstance_ = nullptr;
		/** �X�N���[���̉���. */
		int ScreenBufferW_ = 1200;
		/** �X�N���[���̍���. */
		int ScreenBufferH_ = 675;
		/** �����𑜓x�̉���. */
		int FrameBufferW_ = 1200;
		/** �����𑜓x�̍���. */
		int FrameBufferH_ = 675;
		/** �Q�[���̕\����. */
		string GameName_ = "Game";
	};

	/**
	* �G���W���N���X.
	* �V���O���g���N���X.
	*/
	class EngineSingleton : Noncopyable
	{
	private:

		/**
		* �R���X�g���N�^.
		*/
		EngineSingleton()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~EngineSingleton()
		{
		}

	public:

		/**
		* �C���X�^���X�̎擾.
		*/
		static EngineSingleton& GetInstance()
		{
			static EngineSingleton instance;
			return instance;
		}

		/**
		* �G���W���̏�����.
		*
		* @param initParam	�������p�����[�^.
		*/
		bool Init(const InitParamS& initParam);

		/**
		* ���C�����[�v�̎��s.
		*/
		void RunMainLoop();

		/**
		* D3D11�f�o�C�X�̎擾.
		*/
		ID3D11Device* GetDevice()
		{
			return D3DDevice_;
		}

		/**
		* �����_�����O�R���e�L�X�g�̎擾.
		*/
		RenderContext& GetRenderContext()
		{
			return RenderContext_;
		}

		/**
		* �X���b�v�`�F�C���̎擾.
		*/
		IDXGISwapChain* GetSwapChain()
		{
			return D3DSwapChain_;
		}

		/**
		* �t���[���̕����擾.
		*
		* @return	The frame w.
		*/
		int GetFrameW() const
		{
			return FrameBufferW_;
		}

		/**
		* �t���[���̍������擾.
		*
		* @return	The frame h.
		*/
		int GetFrameH() const
		{
			return FrameBufferH_;
		}

		/**
		* �X�N���[���̕����擾.
		*
		* @return	The screen w.
		*/
		int GetScreenW() const
		{
			return ScreenBufferW_;
		}

		/**
		* �X�N���[���̍������擾.
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
		* �V���h�E�}�b�v�N���X���擾.
		*/
		ShadowMap& GetShadowMap()
		{
			return MainLoop_.ShadowMap_;
		}

		/**
		* ���f���Ǘ��N���X���擾.
		*/
		ModelManager& GetModelManager()
		{
			return ModelManager_;
		}

		/**
		* �f�o�b�O�E�B���h�E�Ǘ��N���X���擾.
		*/
		DebugWindowManager& GetDebugWindowManager()
		{
			return DebugWindowManager_;
		}

		/**
		* �����N���X���擾.
		*/
		Physics& GetPhysics()
		{
			return Physics_;
		}

	private:

		/**
		* �E�B���h�E�̏�����.
		*
		* @param initParam	�������p�����[�^.
		*/
		bool InitWindow(const InitParamS& initParam);

		/**
		* DirectX11�̏�����.
		*
		* @param initParam	�������p�����[�^.
		*/
		bool InitDirectX(const InitParamS& initParam);

		/**
		* �I������.
		*/
		void Final();

		/**
		* �E�B���h�E�v���V�[�W��.
		*/
		static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:

		/** �A�v���P�[�V�����̃C���X�^���X. */
		HINSTANCE hInstance_ = nullptr;
		/** �E�B���h�E�n���h��. */
		HWND hWnd_ = nullptr;
		
		/** �h���C�o�̎�ނ̃I�v�V����. */
		D3D_DRIVER_TYPE D3DDriverType_ = D3D_DRIVER_TYPE_NULL;
		/** Direct3D�f�o�C�X�̃^�[�Q�b�g�ƂȂ�@�\�Z�b�g. */
		D3D_FEATURE_LEVEL D3DFeatureLevel_ = D3D_FEATURE_LEVEL_11_0;
		/** D3D11�f�o�C�X. */
		ID3D11Device* D3DDevice_ = nullptr;
		/** �����_�����O�R���e�L�X�g. */
		RenderContext RenderContext_;
		/** D3D11�����f�o�C�X�R���e�L�X�g. */
		ID3D11DeviceContext* D3DImmediateContext_ = nullptr;
		/** �X���b�v�`�F�C��. */
		IDXGISwapChain* D3DSwapChain_ = nullptr;

		/** ���C�����[�v�N���X. */
		MainLoop MainLoop_;

		/** ���f���Ǘ��N���X. */
		ModelManager ModelManager_;

		/** �����N���X. */
		Physics Physics_;
		
		/** �t���[���o�b�t�@�̕�.�����𑜓x. */
		int FrameBufferW_ = 0;
		/** �t���[���o�b�t�@�̍���.�����𑜓x. */
		int FrameBufferH_ = 0;
		/** �X�N���[���o�b�t�@�̕�. */
		int ScreenBufferW_ = 0;
		/** �X�N���[���o�b�t�@�̍���. */
		int ScreenBufferH_ = 0;

		/** �f�o�b�O�E�B���h�E�Ǘ��N���X. */
		DebugWindowManager DebugWindowManager_;
	
	};

	/**
	* �G���W�����擾.
	*/
	static EngineSingleton& Engine()
	{
		return EngineSingleton::GetInstance();
	}

}
