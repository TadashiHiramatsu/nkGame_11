/**
* モデル描画クラスの実装.
*/
#include"nkstdafx.h"
#include"nkModelRender.h"

namespace nkEngine
{

	/**
	* 初期化.
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

		//頂点シェーダーをロード。
		VShader_.Load("Model", "VSMain", Shader::TypeE::VS);
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
	* 更新.
	*/
	void ModelRender::Update()
	{
		ModelData_.Update();
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

		//頂点シェーダーを設定.
		Engine().GetRenderContext().VSSetShader(VShader_);
		//ピクセルシェーダーを設定.
		Engine().GetRenderContext().PSSetShader(PShader_);
		//入力レイアウトを設定.
		Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

		//サンプラステートを設定.
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
		
			//VSステージの定数バッファを更新.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VSステージの定数バッファを設定.
			Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

			//シャドウテクスチャを設定.
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

			//VSステージの定数バッファを更新.
			Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
			//VSステージの定数バッファを設定.
			Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

			//メッシュ描画.
			it->Render();
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

		for (auto& it : ModelData_.GetMeshList())
		{
			
			vsConstant.WorldMatrix_  = it->GetWorldMatrix();
	
			//VSステージの定数バッファを更新.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VSステージの定数バッファを設定.
			Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

			//メッシュ描画.
			it->Render();
		}
	}

}