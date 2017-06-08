/**
* サンプラステートクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* サンプラステートクラス.
	*/
	class SamplerState : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		SamplerState()
		{
		}

		/**
		* デストラクタ.
		*/
		~SamplerState()
		{
			Release();
		}

		/**
		* 作成.
		*/
		bool Create(
			D3D11_TEXTURE_ADDRESS_MODE addressU,
			D3D11_TEXTURE_ADDRESS_MODE addressV
		);

		/**
		* 解放.
		* デストラクタで呼んでるよ.
		*/
		void Release()
		{
			if (D3DSampler_ != nullptr)
			{
				D3DSampler_->Release();
				D3DSampler_ = nullptr;
			}
		}

		/**
		* D3Dサンプラを取得.
		*/
		ID3D11SamplerState* GetBody()
		{
			return D3DSampler_;
		}

	private:
		
		/** D3Dサンプラクラス. */
		ID3D11SamplerState* D3DSampler_ = nullptr;

	};

}