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
		for (auto& it : ModelData_.GetMeshList())
		{
			//���_�V�F�[�_�[��ݒ�.
			Engine().GetRenderContext().VSSetShader(VShader_);
			//�s�N�Z���V�F�[�_�[��ݒ�.
			Engine().GetRenderContext().PSSetShader(PShader_);
			//���̓��C�A�E�g��ݒ�.
			Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

			VSConstantBufferS vsConstant;
			vsConstant.WorldMatrix_.Transpose(it->GetWorldMatrix());
			vsConstant.ViewMatrix_.Transpose(Camera_->GetViewMatrix());
			vsConstant.ProjMatrix_.Transpose(Camera_->GetProjectionMatrix());
			//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
			Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

			PSConstantBufferS psConstant;
			psConstant.Light_ = *Light_;
			
			psConstant.SRP_.LVMatrix_.Transpose(Engine().GetShadowMap().GetShadowReceiverParam().LVMatrix_);
			psConstant.SRP_.LPMatrix_.Transpose(Engine().GetShadowMap().GetShadowReceiverParam().LPMatrix_);

			Vector4 cameraPos;
			cameraPos.x = Camera_->GetPosition().x;
			cameraPos.y = Camera_->GetPosition().y;
			cameraPos.z = Camera_->GetPosition().z;
			cameraPos.w = 1.0f;
			psConstant.CameraPos_ = cameraPos;
			
			//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
			Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
			//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
			Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

			Engine().GetRenderContext().PSSetShaderResource(0, Engine().GetShadowMap().GetShadowMapSRV());

			it->Render();
		}
	}

	/**
	* �V���h�E�}�b�v�`��.
	*/
	void ModelRender::RenderToShadowMap()
	{
		for (auto& it : ModelData_.GetMeshList())
		{
			//���_�V�F�[�_�[��ݒ�.
			Engine().GetRenderContext().VSSetShader(Engine().GetShadowMap().GetVShader());
			//�s�N�Z���V�F�[�_�[��ݒ�.
			Engine().GetRenderContext().PSSetShader(Engine().GetShadowMap().GetPShader());
			//���̓��C�A�E�g��ݒ�.
			Engine().GetRenderContext().IASetInputLayout(Engine().GetShadowMap().GetVShader().GetInputLayout());

			VSConstantBufferS vsConstant;
			vsConstant.WorldMatrix_.Transpose(it->GetWorldMatrix());
			vsConstant.ViewMatrix_.Transpose(Engine().GetShadowMap().GetShadowReceiverParam().LVMatrix_);
			vsConstant.ProjMatrix_.Transpose(Engine().GetShadowMap().GetShadowReceiverParam().LPMatrix_);
			//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
			Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

			it->Render();
		}
	}

}