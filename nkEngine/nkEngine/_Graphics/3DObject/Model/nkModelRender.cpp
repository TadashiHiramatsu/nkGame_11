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
		for (auto& it : ModelData_.GetMeshList())
		{
			//頂点シェーダーを設定.
			Engine().GetRenderContext().VSSetShader(VShader_);
			//ピクセルシェーダーを設定.
			Engine().GetRenderContext().PSSetShader(PShader_);
			//入力レイアウトを設定.
			Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

			VSConstantBufferS vsConstant;
			vsConstant.WorldMatrix_.Transpose(it->GetWorldMatrix());
			vsConstant.ViewMatrix_.Transpose(Camera_->GetViewMatrix());
			vsConstant.ProjMatrix_.Transpose(Camera_->GetProjectionMatrix());
			//VSステージの定数バッファを更新.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VSステージの定数バッファを設定.
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
			
			//VSステージの定数バッファを更新.
			Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
			//VSステージの定数バッファを設定.
			Engine().GetRenderContext().PSSetConstantBuffer(0, PSConstantBuffer_);

			Engine().GetRenderContext().PSSetShaderResource(0, Engine().GetShadowMap().GetShadowMapSRV());

			it->Render();
		}
	}

	/**
	* シャドウマップ描画.
	*/
	void ModelRender::RenderToShadowMap()
	{
		for (auto& it : ModelData_.GetMeshList())
		{
			//頂点シェーダーを設定.
			Engine().GetRenderContext().VSSetShader(Engine().GetShadowMap().GetVShader());
			//ピクセルシェーダーを設定.
			Engine().GetRenderContext().PSSetShader(Engine().GetShadowMap().GetPShader());
			//入力レイアウトを設定.
			Engine().GetRenderContext().IASetInputLayout(Engine().GetShadowMap().GetVShader().GetInputLayout());

			VSConstantBufferS vsConstant;
			vsConstant.WorldMatrix_.Transpose(it->GetWorldMatrix());
			vsConstant.ViewMatrix_.Transpose(Engine().GetShadowMap().GetShadowReceiverParam().LVMatrix_);
			vsConstant.ProjMatrix_.Transpose(Engine().GetShadowMap().GetShadowReceiverParam().LPMatrix_);
			//VSステージの定数バッファを更新.
			Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
			//VSステージの定数バッファを設定.
			Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

			it->Render();
		}
	}

}