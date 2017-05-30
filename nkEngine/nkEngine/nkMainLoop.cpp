/**
* ���C�����[�v�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkMainLoop.h"

namespace nkEngine
{

	/**
	* ������.
	*/
	bool MainLoop::Init()
	{

		//�}���`�����_�����O�̐ݒ�.
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;

		for (int i = 0; i < 2; i++)
		{
			MainRenderTarget_[i].Create(
				Engine().GetFrameW(),
				Engine().GetFrameH(),
				1,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_FORMAT_D24_UNORM_S8_UINT,
				multiSampleDesc
			);
		}

		//�����_�����O�^�[�Q�b�g�r���[�̐ݒ�.
		Engine().GetRenderContext().OMSetRenderTarget(1, &MainRenderTarget_[CurrentMainRenderTarget_]);

		//�r���[�|�[�g��ݒ�B
		Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, (float)Engine().GetFrameW(), (float)Engine().GetFrameH());

		//�V���h�E�}�b�v�̍쐬.
		ShadowMap_.Create();

		return true;
	}

	/**
	* �X�V.
	*/
	void MainLoop::Update()
	{
		Time().Update();

		NK_LOG("FPS:%f\n", Time().GetFPS());

		Input().Update();

		XInput().Update();

		//�V�[���}�l�[�W���̍X�V.
		SceneManager().Update();

		//����������Ă��Ȃ��I�u�W�F�N�g��������
		GameObjectManager().Start();

		//�v�������_�����O�O�̍X�V
		GameObjectManager().PreUpdate();

		//�X�V
		GameObjectManager().Update();

		//Update�̌�̍X�V
		GameObjectManager().PostUpdate();

		//�V���h�E�}�b�v�̍X�V.
		ShadowMap_.Update();

		//�폜�o�^���ꂽGameObject���폜
		GameObjectManager().Delete();

	}

	/**
	* �`��.
	*/
	void MainLoop::Render()
	{
		//Render�̑O�̕`��
		GameObjectManager().PreRender();

		//�V���h�E�}�b�v�̕`��.
		ShadowMap_.Render();

		//�����_�����O�^�[�Q�b�g�r���[�̐ݒ�.
		Engine().GetRenderContext().OMSetRenderTarget(1, &MainRenderTarget_[CurrentMainRenderTarget_]);

		//�r���[�|�[�g��ݒ�B
		Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, (float)Engine().GetFrameW(), (float)Engine().GetFrameH());

		//�����_�����O�^�[�Q�b�g�r���[��0�Ԗڂ��N���A.
		float clearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
		Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
		Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);

		//�`��
		GameObjectManager().Render();

		//�|�X�g�G�t�F�N�g�̌�̕`��
		GameObjectManager().PostRender();

		//���C�������_�����O�^�[�Q�b�g�̓��e���o�b�N�o�b�t�@�ɃR�s�[.
		CopyMainRenderTargetToBackBuffer();

		//�o�b�N�o�b�t�@�̓��e����ʂɕ`��.
		Engine().GetSwapChain()->Present(0, 0);

	}

	/**
	* ���.
	*/
	void MainLoop::Release()
	{
		//���C�������_�����O�^�[�Q�b�g�̉��.
		for (int i = 0; i < 2; i++)
		{
			MainRenderTarget_[i].Release();
		}
	}

	/**
	* ���C�������_�����O�^�[�Q�b�g�̓��e���o�b�N�o�b�t�@�ɃR�s�[.
	*/
	void MainLoop::CopyMainRenderTargetToBackBuffer()
	{
		//�o�b�N�o�b�t�@.
		ID3D11Texture2D* D3DBackBuffer = NULL;
		//�o�b�N�o�b�t�@���擾.
		Engine().GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&D3DBackBuffer);

		//���C�������_�����O�^�[�Q�b�g���o�b�N�o�b�t�@�ɃR�s�[.
		Engine().GetRenderContext().CopyResource(D3DBackBuffer,MainRenderTarget_[CurrentMainRenderTarget_].GetRenderTarget());
	
		//�o�b�N�o�b�t�@�����.
		D3DBackBuffer->Release();
	
	}

}