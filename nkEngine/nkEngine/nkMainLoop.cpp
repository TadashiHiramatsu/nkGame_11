/**
* ���C�����[�v�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkMainLoop.h"

namespace nkEngine
{
#ifdef DEBUG
	namespace
	{
		const int PLOT_SIZE = 50;
	}
#endif 

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

#ifdef DEBUG
		for (int i = 0; i < PLOT_SIZE; i++)
		{
			FPSList_.push_back(0.0f);
		}
#endif

		return true;
	}

	/**
	* �X�V.
	*/
	void MainLoop::Update()
	{
		Time().Update();

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

#ifdef DEBUG
		ImGui::Begin("GameObject");
		ImGui::SetWindowSize(ImVec2(500.0f, 300.0f));
		ImGui::Text("Hello");
		ImGui::End();

		static int frameCount = 0;
		if (frameCount++ % 10 == 0)
		{
			FPSList_.push_back(Time().GetFPS());
			if (FPSList_.size() > PLOT_SIZE)
			{
				FPSList_.erase(FPSList_.begin());
			}
		}
	

		ImGui::Begin("FPS");
		ImGui::SetWindowSize(ImVec2(100.0f, 100.0f), ImGuiSetCond_FirstUseEver);
		ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
		float FPS = 0.0f;
		if (FPSList_.size() > 0)
		{
			FPS = *(FPSList_.end() - 1);
		}
		ImGui::Text(to_string(FPS).c_str());
		ImGui::PlotLines("FPS�O���t", FPSList_.data(), PLOT_SIZE, 0.0f, nullptr, 0.0f, 120.0f, ImVec2(200.0f, 50.0f));
		ImGui::End();
#endif

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

#ifdef DEBUG
		//Imgui�̕`��.
		ImGui::Render();
#endif

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
		Engine().GetRenderContext().CopyResource(D3DBackBuffer, MainRenderTarget_[CurrentMainRenderTarget_].GetRenderTarget());
	
		//�o�b�N�o�b�t�@�����.
		D3DBackBuffer->Release();
	
	}

}