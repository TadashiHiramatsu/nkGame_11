/**
* バッファの基底クラスの実装.
*/
#include"nkstdafx.h"
#include"nkBuffer.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param initData	初期データ.
	* @param bufferDesc	バッファ定義.
	*/
	bool IBuffer::Create(const void * initData, D3D11_BUFFER_DESC & bufferDesc)
	{
		Release();

		HRESULT hr;

		if (initData)
		{
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = initData;

			hr = Engine().GetDevice()->CreateBuffer(&bufferDesc, &InitData, &D3DBuffer_);
		}
		else
		{
			hr = Engine().GetDevice()->CreateBuffer(&bufferDesc, nullptr, &D3DBuffer_);
		}

		if (FAILED(hr))
		{
			return false;
		}

		return true;

	}

	/**
	* 解放.
	*/
	void IBuffer::Release()
	{
		if (D3DBuffer_ != nullptr)
		{
			D3DBuffer_->Release();
			D3DBuffer_ = nullptr;
		}
	}

}