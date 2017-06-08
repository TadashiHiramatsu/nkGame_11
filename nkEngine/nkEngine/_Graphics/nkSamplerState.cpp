/**
* サンプラステートクラスの実装.
*/
#include"nkstdafx.h"
#include"nkSamplerState.h"

namespace nkEngine
{

	/**
	* 作成.
	*/
	bool SamplerState::Create(
		D3D11_TEXTURE_ADDRESS_MODE addressU,
		D3D11_TEXTURE_ADDRESS_MODE addressV
	)
	{

		HRESULT hr;

		// サンプラーステートの設定
		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(sd));

		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	// フィルタリングメソッド.
		sd.AddressU = addressU;		// 0 ～ 1 の範囲外にあるu座標を解決するために使用されるメソッド.
		sd.AddressV = addressV;		// 0 ～ 1 の範囲外にあるv座標を解決するために使用されるメソッド.
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	// 0 ～ 1 の範囲外にあるw座標を解決するために使用されるメソッド.
		sd.MipLODBias = 0.0f;	//計算されたミップマップ レベルからのオフセット.
		sd.MaxAnisotropy = 16;	// Filter に D3D11_FILTER_ANISOTROPIC または D3D11_FILTER_COMPARISON_ANISOTROPIC が指定されている場合に使用されるクランプ値です。有効な値は 1 ～ 16 です.
		sd.ComparisonFunc = D3D11_COMPARISON_NEVER;	// 既存のサンプリング データに対してデータを比較する関数.
		sd.BorderColor[0] = 0.0f;	// AddressU、AddressV、または AddressW に D3D11_TEXTURE_ADDRESS_BORDER が指定されている場合に使用される境界の色です。0.0 ～ 1.0 の範囲で指定する必要があります.
		sd.BorderColor[1] = 0.0f;	// AddressU、AddressV、または AddressW に D3D11_TEXTURE_ADDRESS_BORDER が指定されている場合に使用される境界の色です。0.0 ～ 1.0 の範囲で指定する必要があります.
		sd.BorderColor[2] = 0.0f;	// AddressU、AddressV、または AddressW に D3D11_TEXTURE_ADDRESS_BORDER が指定されている場合に使用される境界の色です。0.0 ～ 1.0 の範囲で指定する必要があります.
		sd.BorderColor[3] = 0.0f;	// AddressU、AddressV、または AddressW に D3D11_TEXTURE_ADDRESS_BORDER が指定されている場合に使用される境界の色です。0.0 ～ 1.0 の範囲で指定する必要があります.
		sd.MinLOD = 0;	// アクセスをクランプするミップマップ範囲の下限.
		sd.MaxLOD = FLT_MAX;	// アクセスをクランプするミップマップ範囲の上限.

		// サンプラーステート生成
		hr = Engine().GetDevice()->CreateSamplerState(&sd, &D3DSampler_);

		if (FAILED(hr))
		{
			NK_ASSERT(false, "サンプラ作れね");
			return false;
		}

		return true;

	}

}