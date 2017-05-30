/**
* シェーダリソースビュークラスの実装.
*/
#include"nkstdafx.h"
#include"nkShaderResourceView.h"

namespace nkEngine
{

	/**
	* テクスチャ用のSRVを作成.
	*
	* @param texture	テクスチャ.
	*/
	bool ShaderResourceView::Create(ID3D11Texture2D * texture)
	{
		//解放.
		Release();

		if (texture != nullptr)
		{
			//テクスチャの設定.
			D3D11_TEXTURE2D_DESC td;
			texture->GetDesc(&td);

			//シェーダリソースビューの設定.
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			ZeroMemory(&srvd, sizeof(srvd));

			srvd.Format = td.Format;	//フォーマット.
			srvd.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;	//ビューのリソースタイプ.
			srvd.Texture2D.MipLevels = td.MipLevels;	//ミップマップレベル.

			HRESULT hr = Engine().GetDevice()->CreateShaderResourceView(texture, &srvd, &D3DSRV_);
			if (FAILED(hr))
			{
				//作成不可.
				return false;
			}
		}
		else
		{
			//テクスチャない.
			return false;
		}

		//正常終了.
		return true;
	}

	/**
	* 解放.
	* デストラクタで呼んでいる.
	*/
	void ShaderResourceView::Release()
	{
		if (D3DSRV_ != nullptr)
		{
			D3DSRV_->Release();
			D3DSRV_ = nullptr;
		}
	}

}