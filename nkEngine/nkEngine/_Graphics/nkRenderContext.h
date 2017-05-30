/**
* レンダリングコンテキストクラスの定義.
*/
#pragma once

#include"nkShader.h"
#include"Buffer\nkVertexBuffer.h"
#include"Buffer\nkIndexBuffer.h"
#include"Buffer\nkConstantBuffer.h"

#include"_Graphics\nkRenderTarget.h"

namespace nkEngine
{

	/**
	* レンダリングコンテキストクラス.
	* バッファへのレンダリングを行う.
	*/
	class RenderContext : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		RenderContext()
		{
		}

		/**
		* デストラクタ.
		*/
		~RenderContext()
		{
		}

		/**
		* 初期化.
		* 設定したD3Dデバイスコンテキストは初期化側で解放する.
		*
		* @param d3dDeviceContext	D3Dデバイスコンテキスト.
		*/
		void Init(ID3D11DeviceContext* d3dDeviceContext);

		/**
		* レンダリングターゲットビューと深度ステンシルビューを設定.
		* 深度ステンシルビューは一つのものが適応される.
		*
		* @param numView			登録するレンダリングターゲットクラスの数.
		* @param renderTarget		登録するレンダリングターゲットクラス.
		*/
		void OMSetRenderTarget(UINT numView, RenderTarget* renderTarget);

		/**
		* ビューポートの設定.
		*
		* @param topLeftX	ビューポートの左上のX座標.
		* @param topLeftY	ビューポートの左上のY座標.
		* @param width		ビューポートの幅.
		* @param heigth		ビューポートの高さ.
		*/
		void RSSetViewport(float topLeftX, float topLeftY, float width, float heigth)
		{
			Viewport_.Width = width;
			Viewport_.Height = heigth;
			Viewport_.TopLeftX = topLeftX;
			Viewport_.TopLeftY = topLeftY;
			Viewport_.MinDepth = 0.0f;
			Viewport_.MaxDepth = 1.0f;
			D3DDeviceContext_->RSSetViewports(1, &Viewport_);
		}

		/**
		* レンダリングターゲットビューをクリア.
		*
		* @param rtNo		レンダリングターゲットビューの番号.
		* @param clearColor	クリアカラー.		
		*/
		void ClearRenderTargetView(UINT rtNo, float* clearColor)
		{
			if (rtNo < NumRenderTargetView_ && RenderTargetViewList_[rtNo] != nullptr)
			{
				//レンダリングターゲットビューの番号が存在している
				//かつレンダリングターゲットが設定されている.
				D3DDeviceContext_->ClearRenderTargetView(RenderTargetViewList_[rtNo], clearColor);
			}
		}

		/**
		* 深度ステンシルビューのクリア.
		*
		* @param clearFlag	クリアフラグ(D3D11_CLEAR_FLAG列挙型).
		*/
		void ClearDepthStencilView(UINT clearFlag)
		{
			if (DepthStencilView_ != nullptr)
			{
				D3DDeviceContext_->ClearDepthStencilView(DepthStencilView_, clearFlag, 1.0f, 0);
			}
		}

		/**
		* 頂点バッファを設定.
		*
		* @param vertexBuffer	頂点バッファ.
		*/
		void IASetVertexBuffer(VertexBuffer& vertexBuffer)
		{
			UINT offset = 0;
			UINT stride = vertexBuffer.GetStride();
			D3DDeviceContext_->IASetVertexBuffers(
				0,	//使い始めのスロット番号.
				1,	//頂点バッファ配列の要素数.
				&vertexBuffer.GetBody(),	//頂点バッファ.
				&stride,	//頂点バッファーで使用される要素のサイズ.
				&offset	//頂点情報の前にヘッダ情報がある場合変えるっぽい.
			);
		}

		/**
		* インデックスバッファを設定.
		*
		* @param indexBuffer	インデックスバッファ.
		* @param format			フォーマット.
		*/
		void IASetIndexBuffer(IndexBuffer& indexBuffer, DXGI_FORMAT format)
		{
			UINT offset = 0;
			D3DDeviceContext_->IASetIndexBuffer(indexBuffer.GetBody(), format, offset);
		}

		/**
		* プリミティブのトポロジーを設定.
		*
		* @param topology	トポロジー.
		*/
		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			D3DDeviceContext_->IASetPrimitiveTopology(topology);
		}

		/**
		* 頂点シェーダを設定.
		*
		* @param shader	頂点シェーダ.
		*/
		void VSSetShader(Shader& shader)
		{
			D3DDeviceContext_->VSSetShader((ID3D11VertexShader*)shader.GetBody(), nullptr, 0);
		}

		/**
		* ピクセルシェーダを設定.
		*
		* @param shader	ピクセルシェーダ.
		*/
		void PSSetShader(Shader& shader)
		{
			D3DDeviceContext_->PSSetShader((ID3D11PixelShader*)shader.GetBody(), nullptr, 0);
		}

		/**
		* 描画.
		*
		* @param vertexCount			頂点数.
		* @param startVertexLocation	描画を開始する頂点の位置。大抵0で大丈夫.
		*/
		void Draw(UINT vertexCount,UINT startVertexLocation)
		{
			D3DDeviceContext_->Draw(vertexCount, startVertexLocation);
		}

		/**
		* 描画.
		*
		* @param IndexCount	インデックス数.
		* @param StartIndexLocation	.
		* @param BaseVertexLocation	.
		*/
		void DrawIndexed(UINT IndexCount,UINT StartIndexLocation,INT BaseVertexLocation)
		{
			D3DDeviceContext_->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
		}

		/**
		* 入力レイアウトを設定.
		*
		* @param inputLayout	入力レイアウト.
		*/
		void IASetInputLayout(ID3D11InputLayout* inputLayout)
		{
			D3DDeviceContext_->IASetInputLayout(inputLayout);
		}

		/**
		* VSステージに定数バッファを設定.
		*
		* @param slotNo	スロット番号.
		* @param cb		定数バッファ.
		*/
		void VSSetConstantBuffer(UINT slotNo, ConstantBuffer& cb)
		{
			D3DDeviceContext_->VSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}

		/**
		* PSステージに定数バッファを設定.
		*
		* @param slotNo	スロット番号.
		* @param cb		定数バッファ.
		*/
		void PSSetConstantBuffer(UINT slotNo, ConstantBuffer& cb)
		{
			D3DDeviceContext_->PSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}

		/**
		* 頂点シェーダにSRVを設定.
		*
		* @param slotNo	スロット番号.
		* @param srv	シェーダリソースビュー.
		*/
		void VSSetShaderResource(int slotNo, ShaderResourceView& srv)
		{
			D3DDeviceContext_->VSSetShaderResources(slotNo, 1, &srv.GetBody());
		}

		/**
		* ピクセルシェーダにSRVを設定.
		*
		* @param slotNo	スロット番号.
		* @param srv	シェーダリソースビュー.
		*/
		void PSSetShaderResource(int slotNo, ShaderResourceView& srv)
		{
			D3DDeviceContext_->PSSetShaderResources(slotNo, 1, &srv.GetBody());
		}

		/**
		* サブリソースを更新.
		*
		* @param & buffer		コピー先バッファ.
		* @param & srcBuffer	ソースバッファ.
		*/
		template<class TBuffer, class SrcBuffer>
		void UpdateSubresource(TBuffer& buffer, const SrcBuffer& srcBuffer)
		{
			if (buffer.GetBody() != nullptr) 
			{
				D3DDeviceContext_->UpdateSubresource(buffer.GetBody(), 0, nullptr, &srcBuffer, 0, 0);
			}
		}

		/**
		* リソースをコピー.
		*
		* @param destRes	コピー先.
		* @param srcRes	コピー元.
		*/
		template<class TResource>
		void CopyResource(TResource& destRes, TResource& srcRes)
		{
			if (destRes.GetBody() != nullptr&& srcRes.GetBody() != nullptr)
			{
				D3DDeviceContext_->CopyResource(destRes.GetBody(), srcRes.GetBody());
			}
		}
		/**
		* リソースをコピー.
		*
		* @param destRes	コピー先.
		* @param srcRes	コピー元.
		*/
		void CopyResource(ID3D11Resource* destRes, ID3D11Resource* srcRes)
		{
			if (destRes != nullptr&& srcRes != nullptr)
			{
				D3DDeviceContext_->CopyResource(destRes, srcRes);
			}
		}

	private:

		static const int MRT_MAX = 8;	//MRTの最大数.

		/** D3Dデバイスコンテキスト. */
		ID3D11DeviceContext* D3DDeviceContext_ = nullptr;
		/** ビューポート. */
		D3D11_VIEWPORT Viewport_;
		/** 
		* 現在使用されているレンダリングターゲットビュー. 
		* 複数設定したらマルチレンダリングできるのかな？.
		* スワップチェインの初期化も変えなきゃいけないかも.
		*/
		ID3D11RenderTargetView* RenderTargetViewList_[MRT_MAX] = { nullptr };
		/** 現在設定されている深度ステンシルビュー. */
		ID3D11DepthStencilView* DepthStencilView_ = nullptr;
		/** レンダリングターゲットビューの数. */
		UINT NumRenderTargetView_ = 0;
	
	};
}