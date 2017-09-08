/**
* ���f���`��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkModelRender.h"

#include"ModelData\nkMeshNode.h"
#include"ModelData\nkSkinMeshNode.h"

namespace nkEngine
{

	/**
	* ������.
	*/
	void ModelRender::Start(
		Light* light,
		Camera* camera)
	{
		ModelData_ = (ModelData*)GameObject_->FindComponent("ModelData");

		Light_ = light;
		Camera_ = camera;

		//���_�V�F�[�_�[�����[�h�B
		VShader_.Load("Model", "VSMain", Shader::TypeE::VS);
		SkinVShader_.Load("Model","VSSkinMain", Shader::TypeE::VS);
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
		//�T���v���X�e�[�g��ݒ�.
		Engine().GetRenderContext().PSSetSampler(0, 1, &SamplerState_);

		VSConstantBufferS vsConstant;
		vsConstant.ViewMatrix_ = Camera_->GetViewMatrix();
		vsConstant.ProjMatrix_ = Camera_->GetProjectionMatrix();

		PSConstantBufferS psConstant;
		psConstant.Light_ = *Light_;
		psConstant.SRP_.LVMatrix_ = Engine().GetShadowMap().GetLVMatrix();
		psConstant.SRP_.LPMatrix_ = Engine().GetShadowMap().GetLPMatrix();
		Vector3 cameraPos = Camera_->GetPosition();
		psConstant.CameraPos_ = Vector4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f);
		Vector3 cameraTar = Camera_->GetTarget();
		Vector3 dir = Vector3::Zero;
		dir.Sub(cameraTar, cameraPos);
		dir.Normalize();
		psConstant.CameraDir_ = Vector4(dir.x, dir.y, dir.z, 1.0f);
		psConstant.EffectFlag_.z = IsLimLight_;

		for (auto node : ModelData_->GetNodeList())
		{
			if (node->GetNodeType() == INode::NodeTypeE::Mesh)
			{
				//���_�V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().VSSetShader(VShader_);
				//�s�N�Z���V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//���̓��C�A�E�g��ݒ�.
				Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

				//���b�V���N���X�ɃL���X�g.
				MeshNode* mesh = (MeshNode*)node;

				//���[���h�s���ݒ�.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//�V���h�E�e�N�X�`����ݒ�.
				Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::ShadowTexture, Engine().GetShadowMap().GetShadowMapSRV());

				if (mesh->GetMaterialNum() != -1)
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::DiffuseTexture, ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->GetTextureSRV());

					if (ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->isNormalMap())
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->GetNormalTextureSRV());
						psConstant.EffectFlag_.x = true;
					}
					else
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, nullptr);
						psConstant.EffectFlag_.x = false;
					}

					if (ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->isSpecularMap())
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->GetSpecularTextureSRV());
						psConstant.EffectFlag_.y = true;
					}
					else
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, nullptr);
						psConstant.EffectFlag_.y = false;
					}
				}
				else
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::DiffuseTexture, nullptr);
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, nullptr);
					psConstant.EffectFlag_.x = false;
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, nullptr);
					psConstant.EffectFlag_.y = false;
				}

				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

				//���b�V���`��.
				mesh->RenderWrapper();
			}
			else if (node->GetNodeType() == INode::NodeTypeE::SkinMesh)
			{
				//���_�V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().VSSetShader(SkinVShader_);
				//�s�N�Z���V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//���̓��C�A�E�g��ݒ�.
				Engine().GetRenderContext().IASetInputLayout(SkinVShader_.GetInputLayout());
				//���b�V���N���X�ɃL���X�g.
				SkinMeshNode* mesh = (SkinMeshNode*)node;

				//���[���h�s���ݒ�.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//�V���h�E�e�N�X�`����ݒ�.
				Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::ShadowTexture, Engine().GetShadowMap().GetShadowMapSRV());

				if (mesh->GetMaterialNum() != -1)
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::DiffuseTexture, ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->GetTextureSRV());

					if (ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->isNormalMap())
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->GetNormalTextureSRV());
						psConstant.EffectFlag_.x = true;
					}
					else
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, nullptr);
						psConstant.EffectFlag_.x = false;
					}

					if (ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->isSpecularMap())
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, ModelData_->GetMaterialList()[mesh->GetMaterialNum()]->GetSpecularTextureSRV());
						psConstant.EffectFlag_.y = true;
					}
					else
					{
						Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, nullptr);
						psConstant.EffectFlag_.y = false;
					}
				}
				else
				{
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::DiffuseTexture, nullptr);
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::NormalTexture, nullptr);
					psConstant.EffectFlag_.x = false;
					Engine().GetRenderContext().PSSetShaderResource(ShaderResourceCodeE::SpecularTexture, nullptr);
					psConstant.EffectFlag_.y = false;
				}

				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

				//���b�V���`��.
				mesh->RenderWrapper();
			}
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

		for (auto node : ModelData_->GetNodeList())
		{
			if (node->GetNodeType() == INode::NodeTypeE::Mesh)
			{
				//���b�V���N���X�ɃL���X�g.
				MeshNode* mesh = (MeshNode*)node;

				//���[���h�s���ݒ�.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//���b�V���`��.
				mesh->RenderWrapper();
			}
			else if (node->GetNodeType() == INode::NodeTypeE::SkinMesh)
			{
				//���b�V���N���X�ɃL���X�g.
				SkinMeshNode* mesh = (SkinMeshNode*)node;

				//���[���h�s���ݒ�.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//���b�V���`��.
				mesh->RenderWrapper();
			}
		}
	}

}