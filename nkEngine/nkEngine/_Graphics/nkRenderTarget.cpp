/**
* レンダリングターゲットクラスの実装.
*/
#include"nkstdafx.h"
#include"nkRenderTarget.h"

namespace nkEngine
{

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
	bool RenderTarget::Create(
		int w, 
		int h,	
		int mipLevel,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat,
		DXGI_SAMPLE_DESC multiSampleDesc)
	{
		HRESULT hr = E_FAIL;

		Size_ = Vector2(w, h);

		//レンダリングターゲットの作成。
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));

		td.Width = w;	//幅.
		td.Height = h;	//高さ.
		td.MipLevels = mipLevel;	//ミップレベル.
		td.ArraySize = 1;	//テクスチャ配列内のテクスチャの数.
		td.Format = colorFormat;	//フォーマット.
		td.SampleDesc = multiSampleDesc;	//マルチサンプリングパラメータ.
		td.Usage = D3D11_USAGE_DEFAULT;		//読み込み書き込み設定.
		td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;	//バインドフラグ.
		td.CPUAccessFlags = 0;	//CPUサクセスフラグ(0:アクセス不要).
		td.MiscFlags = 0;	//他の一般性の低いリソースオプション(0:使用しない).

		hr = Engine().GetDevice()->CreateTexture2D(&td, nullptr, &D3DRenderTargetTexture_);
		if (FAILED(hr)) 
		{
			//レンダリングターゲットの作成に失敗.
			return false;
		}

		//レンダリングターゲットビューを作成.
		hr = Engine().GetDevice()->CreateRenderTargetView(D3DRenderTargetTexture_, nullptr, &D3DRenderTargetView_);
		if (FAILED(hr))
		{
			//レンダリングターゲットビューを作成出来なかった.
			return false;
		}

		RenderTargetSRV_.Create(D3DRenderTargetTexture_);

		if (depthStencilFormat != DXGI_FORMAT_UNKNOWN)
		{
			//作成.
			
			//深度ステンシルテクスチャの作成.
			td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

			hr = Engine().GetDevice()->CreateTexture2D(&td, NULL, &D3DDepthStencilTexture_);
			if (FAILED(hr))
			{
				return false;
			}

			//深度ステンシルビューの作成.
			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format = td.Format;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;
			hr = Engine().GetDevice()->CreateDepthStencilView(D3DDepthStencilTexture_, &descDSV, &D3DDepthStencilView_);
			if (FAILED(hr))
			{
				return false;
			}

		}

		return true;

	}

	/**
	* 解放.
	*/
	void RenderTarget::Release()
	{
		if (D3DRenderTargetTexture_ != nullptr)
		{
			D3DRenderTargetTexture_->Release();
			D3DRenderTargetTexture_ = nullptr;
		}
		if (D3DRenderTargetView_ != nullptr)
		{
			D3DRenderTargetView_->Release();
			D3DRenderTargetView_ = nullptr;
		}
		if (D3DDepthStencilTexture_ != nullptr)
		{
			D3DDepthStencilTexture_->Release();
			D3DDepthStencilTexture_ = nullptr;
		}
		if (D3DDepthStencilView_ != nullptr)
		{
			D3DDepthStencilView_->Release();
			D3DDepthStencilView_ = nullptr;
		}
	}

}