/**
* 定数バッファクラスの定義.
*/
#pragma once

#include"nkBuffer.h"

namespace nkEngine
{

	/**
	* 定数バッファクラス.
	*/
	class ConstantBuffer : public IBuffer
	{
	public:

		/**
		* コンストラクタ.
		*/
		ConstantBuffer()
		{
		}

		/**
		* デストラクタ.
		*/
		~ConstantBuffer()
		{
		}

		/**
		* 作成.
		*
		* @param initData	初期データ.
		* @param bufferSize	バッファサイズ.
		*/
		bool Create(const void* initData, UINT bufferSize);

	private:

	};

}