/**
* レンダリングターゲットクラスの定義.
*/
#pragma once

#include"View\nkShaderResourceView.h"

namespace nkEngine
{

	/**
	* レンダリングターゲットクラス.
	*/
	class RenderTarget : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		RenderTarget()
		{
		}

		/**
		* デストラクタ.
		*/
		~RenderTarget()
		{
			Release();
		}

		/**
		* 作成.
		*
		* @param w						幅.
		* @param h						高さ.
		* @param mipLevel				ミップマップレベル.
		* @param colorFormat			カラーバッファのフォーマット.
		* @param depthStencilFormat		深度ステンシルバッファのフォーマット.
		* @param multiSampleDesc		マルチサンプリングの定義.
		*/
		bool Create(
			int w, 
			int h, 
			int mipLevel, 
			DXGI_FORMAT colorFormat,
			DXGI_FORMAT depthStencilFormat,
			DXGI_SAMPLE_DESC multiSampleDesc
		);

		/**
		* 解放. 
		*/
		void Release();

		/**
		* レンダリングターゲットを取得.
		*/
		ID3D11Texture2D* GetRenderTarget()
		{
			return D3DRenderTargetTexture_;
		}

		/**
		* レンダリングターゲットビューを取得.
		*/
		ID3D11RenderTargetView* GetRenderTargetView()
		{
			return D3DRenderTargetView_;
		}

		/**
		* 深度ステンシルビューを取得.
		*/
		ID3D11DepthStencilView* GetDepthStencilView()
		{
			return D3DDepthStencilView_;
		}

		/**
		* レンダリングターゲット用SRVを取得.
		*/
		ShaderResourceView& GetRenderTargetSRV()
		{
			return RenderTargetSRV_;
		}

		/**
		* サイズの取得.
		*/
		const Vector2& GetSize()
		{
			return Size_;
		}

	private:

		/** レンダリングターゲットテクスチャ. */
		ID3D11Texture2D* D3DRenderTargetTexture_ = nullptr;
		/** レンダリングターゲット. */
		ID3D11RenderTargetView*	D3DRenderTargetView_ = nullptr;
		/** レンダリングターゲット用SRV. */
		ShaderResourceView RenderTargetSRV_;
		/** 深度ステンシルテクスチャ. */
		ID3D11Texture2D* D3DDepthStencilTexture_ = nullptr;
		/** 深度ステンシルビュー. */
		ID3D11DepthStencilView* D3DDepthStencilView_ = nullptr;

		/** レンダリングターゲットのサイズ. */
		Vector2 Size_ = Vector2::Zero;
	
	};

}