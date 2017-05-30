/**
* インデックスバッファクラスの実装.
*/
#include"nkstdafx.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param srcIndexBuffer	ソースインデックスバッファ.
	* @param indexNum		インデックス数.
	*/
	bool IndexBuffer::Create(const void * srcIndexBuffer, UINT indexNum)
	{
		//インデックスバッファ作成
		D3D11_BUFFER_DESC bd;
		bd.ByteWidth = sizeof(USHORT) * indexNum;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		//bd.StructureByteStride = sizeof(USHORT);

		return IBuffer::Create(srcIndexBuffer, bd);

	}

}