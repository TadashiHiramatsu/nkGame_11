/**
* インデックスバッファクラスの定義.
*/
#pragma once

#include"_Graphics\Buffer\nkBuffer.h"

namespace nkEngine
{

	/**
	* インデックスバッファクラス.
	*/
	class IndexBuffer : public IBuffer
	{
	public:

		/**
		* コンストラクタ.
		*/
		IndexBuffer()
		{
		}
		
		/**
		* デストラクタ.
		*/
		~IndexBuffer()
		{
		}

		/**
		* 作成.
		*
		* @param srcIndexBuffer	ソースインデックスバッファ.
		* @param indexNum		インデックス数.
		*/
		bool Create(const void* srcIndexBuffer, UINT indexNum);

	private:

	};
}