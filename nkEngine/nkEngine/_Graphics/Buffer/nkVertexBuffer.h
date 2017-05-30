/**
* 頂点バッファクラスの定義.
*/
#pragma once

#include"nkBuffer.h"

namespace nkEngine
{

	/**
	* 頂点バッファクラス.
	*/
	class VertexBuffer : public IBuffer
	{
	public:

		/**
		* コンストラクタ.
		*/
		VertexBuffer()
		{
		}

		/**
		* デストラクタ.
		*/
		~VertexBuffer()
		{
		}

		/**
		* 作成.
		*
		* @param srcVertexBuffer	ソース頂点バッファ.
		* @param numVertex	頂点数.
		* @param stride		頂点ストライド.
		*/
		bool Create(const void* srcVertexBuffer, int numVertex, int stride);

		/**
		* 頂点ストライドの取得.
		*/
		int GetStride() const
		{
			return Stride_;
		}

	private:
		
		/** 頂点ストライド. */
		int Stride_ = 0;

	};

}