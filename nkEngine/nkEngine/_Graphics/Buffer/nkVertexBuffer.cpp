/**
* 頂点バッファクラスの実装.
*/
#include"nkstdafx.h"
#include"nkVertexBuffer.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param srcVertexBuffer	ソース頂点バッファ.
	* @param numVertex			頂点数.
	* @param stride				頂点ストライド.
	*/
	bool VertexBuffer::Create(const void * srcVertexBuffer, int numVertex, int stride)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DEFAULT;	//バッファーで想定されている読み込みおよび書き込みの方法を識別.
		bd.ByteWidth = stride * numVertex;	//バッファのサイズ(バイト単位).
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//バッファーをどのようにパイプラインにバインドするかを識別.
		bd.CPUAccessFlags = 0;	//CPUアクセスのフラグ(CPUアクセスが必要でない場合は0).

		//ストライドの設定.
		Stride_ = stride;
		
		return IBuffer::Create(srcVertexBuffer, bd);
	}

}