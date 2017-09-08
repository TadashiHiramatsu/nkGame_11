/**
* モデル描画クラスの実装.
*/
#include"nkstdafx.h"
#include"nkModelRender.h"

#include"ModelData\nkMeshNode.h"
#include"ModelData\nkSkinMeshNode.h"

namespace nkEngine
{

	/**
	* 初期化.
	*/
	void ModelRender::Start(
		Light* light,
		Camera* camera)
	{
		ModelData_ = (ModelData*)GameObject_->FindComponent("ModelData");

		Light_ = light;
		Camera_ = camera;

		//頂点シェーダーをロード。
		VShader_.Load("Model", "VSMain", Shader::TypeE::VS);
		SkinVShader_.Load("Model","VSSkinMain", Shader::TypeE::VS);
		//ピクセルシェーダーをロード。
		PShader_.Load("Model", "PSMain", Shader::TypeE::PS);

		//VSステージの定数バッファを作成.
		VSConstantBuffer_.Create(nullptr, sizeof(VSConstantBufferS));
		//PSステージの定数バッファを作成.
		PSConstantBuffer_.Create(nullptr, sizeof(PSConstantBufferS));

		//サンプラステートを作成.
		SamplerState_.Create(D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP);

	}

	/**
	* Render前の描画.
	*/
	void ModelRender::PreRender()
	{
		Engine().GetShadowMap().Entry(this);
	}

	/**
	* 描画.
	*/
	void ModelRender::Render()
	{
		//サンプラステートを設定.
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
				//頂点シェーダーを設定.
				Engine().GetRenderContext().VSSetShader(VShader_);
				//ピクセルシェーダーを設定.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//入力レイアウトを設定.
				Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

				//メッシュクラスにキャスト.
				MeshNode* mesh = (MeshNode*)node;

				//ワールド行列を設定.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//シャドウテクスチャを設定.
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

				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

				//メッシュ描画.
				mesh->RenderWrapper();
			}
			else if (node->GetNodeType() == INode::NodeTypeE::SkinMesh)
			{
				//頂点シェーダーを設定.
				Engine().GetRenderContext().VSSetShader(SkinVShader_);
				//ピクセルシェーダーを設定.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//入力レイアウトを設定.
				Engine().GetRenderContext().IASetInputLayout(SkinVShader_.GetInputLayout());
				//メッシュクラスにキャスト.
				SkinMeshNode* mesh = (SkinMeshNode*)node;

				//ワールド行列を設定.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//シャドウテクスチャを設定.
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

				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

				//メッシュ描画.
				mesh->RenderWrapper();
			}
		}
	}

	/**
	* シャドウマップ描画.
	*/
	void ModelRender::RenderToShadowMap()
	{

		//頂点シェーダーを設定.
		Engine().GetRenderContext().VSSetShader(Engine().GetShadowMap().GetVShader());
		//ピクセルシェーダーを設定.
		Engine().GetRenderContext().PSSetShader(Engine().GetShadowMap().GetPShader());
		//入力レイアウトを設定.
		Engine().GetRenderContext().IASetInputLayout(Engine().GetShadowMap().GetVShader().GetInputLayout());

		VSConstantBufferS vsConstant;
		vsConstant.ViewMatrix_ = Engine().GetShadowMap().GetLVMatrix();
		vsConstant.ProjMatrix_ = Engine().GetShadowMap().GetLPMatrix();

		for (auto node : ModelData_->GetNodeList())
		{
			if (node->GetNodeType() == INode::NodeTypeE::Mesh)
			{
				//メッシュクラスにキャスト.
				MeshNode* mesh = (MeshNode*)node;

				//ワールド行列を設定.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//メッシュ描画.
				mesh->RenderWrapper();
			}
			else if (node->GetNodeType() == INode::NodeTypeE::SkinMesh)
			{
				//メッシュクラスにキャスト.
				SkinMeshNode* mesh = (SkinMeshNode*)node;

				//ワールド行列を設定.
				vsConstant.WorldMatrix_ = mesh->GetWorldMatrix();

				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//メッシュ描画.
				mesh->RenderWrapper();
			}
		}
	}

}