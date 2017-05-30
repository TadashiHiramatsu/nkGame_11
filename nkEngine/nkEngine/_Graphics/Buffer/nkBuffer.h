/**
* バッファの基底クラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* バッファの基底クラス.
	*/
	class IBuffer : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		IBuffer()
		{
		}

		/**
		* デストラクタ.
		*/
		virtual ~IBuffer()
		{
		}

		/**
		* 作成.
		*
		* @param initData	初期データ.
		* @param bufferDesc	バッファ定義.
		*/
		bool Create(const void* initData, D3D11_BUFFER_DESC& bufferDesc);

		/**
		* 解放.
		*/
		void Release();

		/**
		* ID3D11Buffer*取得.
		*/
		ID3D11Buffer*& GetBody()
		{
			return D3DBuffer_;
		}

	protected:

		/** バッファ. */
		ID3D11Buffer* D3DBuffer_ = nullptr;

	};

}