/**
* ブラークラスの実装.
*/
#include"nkstdafx.h"
#include"nkBlur.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param w		横.
	* @param h		高さ.
	* @param srcSRV	元となるSRV.
	*/
	void Blur::Create(int w, int h, ShaderResourceView & srcSRV)
	{
		//元となるSRV.
		SrcSRV_ = &srcSRV;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		SrcSRV_->GetBody()->GetDesc(&srvd);
	
		//サイズを設定.
		SrcTexSize = Vector2(w, h);

		//ブラーサイズを作成
		int  size[2][2]
		{
			{ w >> 1, h },
			{ w >> 1, h >> 1 },
		};

		//マルチレンダリングの設定.
		DXGI_SAMPLE_DESC md;
		md.Count = 1;
		md.Quality = 0;
		//レンダリングターゲットの作成
		for (int i = 0; i < 2; i++)
		{
			BlurRT_[i].Create(size[i][0], size[i][1], 1, srvd.Format, DXGI_FORMAT_D24_UNORM_S8_UINT, md);
		}

		static VertexBufferS vertex[] =
		{
			{ Vector4(-1.0f	, 1.0f	, 0.0f, 1.0f),Vector2(0.0f, 0.0f)},
			{ Vector4(1.0f	, 1.0f	, 0.0f, 1.0f),Vector2(1.0f, 0.0f)},
			{ Vector4(-1.0f	, -1.0f	, 0.0f, 1.0f),Vector2(0.0f, 1.0f)},
			{ Vector4(1.0f	, -1.0f	, 0.0f, 1.0f),Vector2(1.0f, 1.0f)},
		};

		VertexBuffer_.Create(vertex, 4, sizeof(VertexBufferS));

		//頂点シェーダーをロード。
		VShaderXBlur_.Load("Blur", "VSBlur_X", Shader::TypeE::VS);
		VShaderYBlur_.Load("Blur", "VSBlur_Y", Shader::TypeE::VS);
		//ピクセルシェーダーをロード。
		PShader_.Load("Blur", "PSBlur", Shader::TypeE::PS);

		//VSステージの定数バッファを作成.
		VSConstantBuffer_.Create(nullptr, sizeof(VSConstantBufferS));

	}

	/**
	* 描画.
	*/
	void Blur::Render()
	{
		if (SrcSRV_ != nullptr)
		{
			//Xブラー.
			{
				//レンダリングターゲットを設定.
				Engine().GetRenderContext().OMSetRenderTarget(1, &BlurRT_[0]);

				//レンダリングターゲットビューの0番目をクリア.
				float clearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
				Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
				Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);

				//ビューポートを設定。
				Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, BlurRT_[0].GetSize().x, BlurRT_[0].GetSize().y);

				//頂点バッファを設定.
				Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);

				//プリミティブのトポロジーを設定.
				Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				//頂点シェーダーを設定.
				Engine().GetRenderContext().VSSetShader(VShaderXBlur_);
				//ピクセルシェーダーを設定.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//入力レイアウトを設定.
				Engine().GetRenderContext().IASetInputLayout(VShaderXBlur_.GetInputLayout());

				VSConstantBufferS vsConstant;
				vsConstant.TexSize_ = SrcTexSize;
				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//テクスチャを設定.
				Engine().GetRenderContext().PSSetShaderResource(0, *SrcSRV_);

				//描画。
				Engine().GetRenderContext().Draw(4, 0);
			}
			//Yブラー
			{
				//レンダリングターゲットを設定.
				Engine().GetRenderContext().OMSetRenderTarget(1, &BlurRT_[1]);

				//レンダリングターゲットビューの0番目をクリア.
				float clearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
				Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
				Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);

				//ビューポートを設定。
				Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, BlurRT_[1].GetSize().x, BlurRT_[1].GetSize().y);

				//頂点バッファを設定.
				Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);

				//プリミティブのトポロジーを設定.
				Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				//頂点シェーダーを設定.
				Engine().GetRenderContext().VSSetShader(VShaderYBlur_);
				//ピクセルシェーダーを設定.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//入力レイアウトを設定.
				Engine().GetRenderContext().IASetInputLayout(VShaderYBlur_.GetInputLayout());

				VSConstantBufferS vsConstant;
				vsConstant.TexSize_ = BlurRT_[0].GetSize();
				//VSステージの定数バッファを更新.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VSステージの定数バッファを設定.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//テクスチャを設定.
				Engine().GetRenderContext().PSSetShaderResource(0, BlurRT_[0].GetRenderTargetSRV());

				//描画。
				Engine().GetRenderContext().Draw(4, 0);
			}
		}
	}

}