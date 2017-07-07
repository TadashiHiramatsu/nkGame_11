/**
* �V���h�E�}�b�v�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkShadowMap.h"

namespace nkEngine
{

	/**
	* �쐬.
	*/
	void ShadowMap::Create()
	{
		//���.
		Release();

		//�L���t���O��ݒ�.
		isEnable_ = true;

		Near_ = 1.0f;
		Far_ = 100.0f;

		int w = 2048;
		int h = 2048;

		Aspect_ = (float)w / h;

		Vector3 dld = Vector3(-1.0f, 1.0f, -1.0f);
		dld.Normalize();
		LightPosition_ = dld;

		//�}���`�����_�����O�̐ݒ�.
		DXGI_SAMPLE_DESC md;
		md.Count = 1;
		md.Quality = 0;

		//�V���h�E�}�b�v�pRT���쐬.
		ShadowMapRT_.Create(w, h, 1, DXGI_FORMAT_R16G16_FLOAT, DXGI_FORMAT_D24_UNORM_S8_UINT, md);

		//�u���[�쐬.
		Blur_.Create(w, h, ShadowMapRT_.GetRenderTargetSRV());

		//�V���h�E�G���A��ݒ�.
		ShadowArea_ = Vector2(10.0f, 10.0f);

		//���_�V�F�[�_�[�����[�h�B
		VShader_.Load("ShadowMap", "VSShadowMap", Shader::TypeE::VS);
		//�s�N�Z���V�F�[�_�[�����[�h�B
		PShader_.Load("ShadowMap", "PSShadowMap", Shader::TypeE::PS);

	}

	/**
	* �X�V.
	*/
	void ShadowMap::Update()
	{
		if (isEnable_)
		{
			//���C�g�̌���.
			Vector3 lightDirection = Vector3::Zero;
			lightDirection.Sub(LightTarget_, LightPosition_);
			lightDirection.Normalize();

			//���C�g�̏����.
			Vector3 lightUp;

			//���C�g�̌����̊p�x���v�Z.
			float angle = fabsf(lightDirection.Dot(Vector3::Up));

			if (fabsf((angle - 1.0f)) < 0.0001f)
			{
				lightUp = Vector3::Right;
			}
			else
			{
				lightUp = Vector3::Up;
			}

			//���C�g�r���[�s��.
			LVMatrix_.MakeLookAtLH(LightPosition_, LightTarget_, lightUp);

			//���C�g�v���W�F�N�V�����s��.
			LPMatrix_.MakeOrthoProjectionLH(ShadowArea_.x * Aspect_, ShadowArea_.y, Near_, Far_);

		}
	}

	/**
	* �`��.
	*/
	void ShadowMap::Render()
	{
		if (isEnable_)
		{
			Engine().GetRenderContext().OMSetRenderTarget(1, &ShadowMapRT_);
		
			//�����_�����O�^�[�Q�b�g�r���[��0�Ԗڂ��N���A.
			float clearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
			Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
			Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);
			
			//�r���[�|�[�g��ݒ�B
			Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, ShadowMapRT_.GetSize().x, ShadowMapRT_.GetSize().y);

			for (auto& it : CasterModelList_)
			{
				it->RenderToShadowMap();
			}

			//�u���[�`��.
			Blur_.Render();

			//���f�����X�g���N���A.
			CasterModelList_.clear();

		}
	}

	/**
	* ���.
	*/
	void ShadowMap::Release()
	{
		ShadowMapRT_.Release();
	}

}