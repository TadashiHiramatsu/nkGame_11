/**
* ���f���`��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkModelRender.h"

namespace nkEngine
{

	/**
	* ������.
	*/
	void ModelRender::Init(
		string fileName, 
		Transform* parent,
		Light* light,
		Camera* camera)
	{
		ModelData_.Load(fileName, parent);

		Light_ = light;
		Camera_ = camera;

		//���_�V�F�[�_�[�����[�h�B
		VShader_.Load("Model", "VSMain", Shader::TypeE::VS);
		//�s�N�Z���V�F�[�_�[�����[�h�B
		PShader_.Load("Model", "PSMain", Shader::TypeE::PS);

		//VS�X�e�[�W�̒萔�o�b�t�@���쐬.
		VSConstantBuffer_.Create(nullptr, sizeof(VSConstantBufferS));
		//PS�X�e�[�W�̒萔�o�b�t�@���쐬.
		PSConstantBuffer_.Create(nullptr, sizeof(PSConstantBufferS));

		//�T���v���X�e�[�g���쐬.
		SamplerState_.Create(D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP);

	}

	/**
	* �X�V.
	*/
	void ModelRender::Update()
	{
		ModelData_.Update();
	}

	/**
	* Render�O�̕`��.
	*/
	void ModelRender::PreRender()
	{
		Engine().GetShadowMap().Entry(this);
	}

	/**
	* �`��.
	*/
	void ModelRender::Render()
	{

		//���_�V�F�[�_�[��ݒ�.
		Engine().GetRenderContext().VSSetShader(VShader_);
		//�s�N�Z���V�F�[�_�[��ݒ�.
		Engine().GetRenderContext().PSSetShader(PShader_);
		//���̓��C�A�E�g��ݒ�.
		Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

		//�T���v���X�e�[�g��ݒ�.
		Engine().GetRenderContext().PSSetSampler(0, 1, &SamplerState_);

		VSConstantBufferS vsConstant;
		vsConstant.ViewMatrix_ = Camera_->GetViewMatrix();
		vsConstant.ProjMatrix_ = Camera_->GetProjectionMatrix();

		PSConstantBufferS psConstant;
		psConstant.Light_ = *Light_;
		psConstant.SRP_.LVMatrix_ = Engine().GetShadowMap().GetLVMatrix();
		psConstant.SRP_.LPMatrix_ = Engine().GetShadowMap().GetLPMatrix();
		Vector4 cameraPos;
		cameraPos.x = Camera_->GetPosition().x;
		cameraPos.y = Camera_->GetPosition().y;
		cameraPos.z = Camera_->GetPosition().z;
		cameraPos.w = 1.0f;
		psConstant.CameraPos_ = cameraPos;

		for (auto& it : ModelData_.GetMeshList())
		{
			
			vsConstant.WorldMatrix_ = it->GetWorldMatrix();
		
			//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
			Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

			//�V���h�E�e�N�X�`����ݒ�.
			Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::ShadowTexture, Engine().GetShadowMap().GetShadowMapSRV());

			if (it->GetMaterialNum() != -1)
			{
				Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::DiffuseTexture, ModelData_.GetMaterialList()[it->GetMaterialNum()]->GetTextureSRV());

				if (ModelData_.GetMaterialList()[it->GetMaterialNum()]->isNormalMap())
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, ModelData_.GetMaterialList()[it->GetMaterialNum()]->GetNormalTextureSRV());
					psConstant.EffectFlag_.x = 1.0f;
				}
				else
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, nullptr);
					psConstant.EffectFlag_.x = 0.0f;
				}

				if (ModelData_.GetMaterialList()[it->GetMaterialNum()]->isSpecularMap())
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, ModelData_.GetMaterialList()[it->GetMaterialNum()]->GetSpecularTextureSRV());
					psConstant.EffectFlag_.y = 1.0f;
				}
				else
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, nullptr);
					psConstant.EffectFlag_.y = 0.0f;
				}
			}

			//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
			Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
			//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
			Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

			//���b�V���`��.
			it->Render();
		}
	}

	/**
	* �V���h�E�}�b�v�`��.
	*/
	void ModelRender::RenderToShadowMap()
	{

		//���_�V�F�[�_�[��ݒ�.
		Engine().GetRenderContext().VSSetShader(Engine().GetShadowMap().GetVShader());
		//�s�N�Z���V�F�[�_�[��ݒ�.
		Engine().GetRenderContext().PSSetShader(Engine().GetShadowMap().GetPShader());
		//���̓��C�A�E�g��ݒ�.
		Engine().GetRenderContext().IASetInputLayout(Engine().GetShadowMap().GetVShader().GetInputLayout());

		VSConstantBufferS vsConstant;
		vsConstant.ViewMatrix_ = Engine().GetShadowMap().GetLVMatrix();
		vsConstant.ProjMatrix_ = Engine().GetShadowMap().GetLPMatrix();

		for (auto& it : ModelData_.GetMeshList())
		{
			
			vsConstant.WorldMatrix_  = it->GetWorldMatrix();
	
			//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
			Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

			//���b�V���`��.
			it->Render();
		}
	}

}