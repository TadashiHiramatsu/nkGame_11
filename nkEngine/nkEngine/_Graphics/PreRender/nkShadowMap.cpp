/**
* シャドウマップクラスの実装.
*/
#include"nkstdafx.h"
#include"nkShadowMap.h"

namespace nkEngine
{

	/**
	* 作成.
	*/
	void ShadowMap::Create()
	{
		//解放.
		Release();

		//有効フラグを設定.
		isEnable_ = true;

		Near_ = 1.0f;
		Far_ = 100.0f;

		int w = 2048;
		int h = 2048;

		Aspect_ = (float)w / h;

		Vector3 dld = Vector3(-1.0f, 1.0f, -1.0f);
		dld.Normalize();
		LightPosition_ = dld;

		//マルチレンダリングの設定.
		DXGI_SAMPLE_DESC md;
		md.Count = 1;
		md.Quality = 0;

		//シャドウマップ用RTを作成.
		ShadowMapRT_.Create(w, h, 1, DXGI_FORMAT_R16G16_FLOAT, DXGI_FORMAT_D24_UNORM_S8_UINT, md);

		//ブラー作成.
		Blur_.Create(w, h, ShadowMapRT_.GetRenderTargetSRV());

		//シャドウエリアを設定.
		ShadowArea_ = Vector2(10.0f, 10.0f);

		//頂点シェーダーをロード。
		VShader_.Load("ShadowMap", "VSShadowMap", Shader::TypeE::VS);
		//ピクセルシェーダーをロード。
		PShader_.Load("ShadowMap", "PSShadowMap", Shader::TypeE::PS);

	}

	/**
	* 更新.
	*/
	void ShadowMap::Update()
	{
		if (isEnable_)
		{
			//ライトの向き.
			Vector3 lightDirection = Vector3::Zero;
			lightDirection.Sub(LightTarget_, LightPosition_);
			lightDirection.Normalize();

			//ライトの上方向.
			Vector3 lightUp;

			//ライトの向きの角度を計算.
			float angle = fabsf(lightDirection.Dot(Vector3::Up));

			if (fabsf((angle - 1.0f)) < 0.0001f)
			{
				lightUp = Vector3::Right;
			}
			else
			{
				lightUp = Vector3::Up;
			}

			//ライトビュー行列.
			LVMatrix_.MakeLookAtLH(LightPosition_, LightTarget_, lightUp);

			//ライトプロジェクション行列.
			LPMatrix_.MakeOrthoProjectionLH(ShadowArea_.x * Aspect_, ShadowArea_.y, Near_, Far_);

		}
	}

	/**
	* 描画.
	*/
	void ShadowMap::Render()
	{
		if (isEnable_)
		{
			Engine().GetRenderContext().OMSetRenderTarget(1, &ShadowMapRT_);
		
			//レンダリングターゲットビューの0番目をクリア.
			float clearColor[4] = { 0.0f,0.0f,0.0f,1.0f };
			Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
			Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);
			
			//ビューポートを設定。
			Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, ShadowMapRT_.GetSize().x, ShadowMapRT_.GetSize().y);

			for (auto& it : CasterModelList_)
			{
				it->RenderToShadowMap();
			}

			//ブラー描画.
			Blur_.Render();

			//モデルリストをクリア.
			CasterModelList_.clear();

		}
	}

	/**
	* 解放.
	*/
	void ShadowMap::Release()
	{
		ShadowMapRT_.Release();
	}

}