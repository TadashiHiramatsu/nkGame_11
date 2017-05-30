/**
* 定数バッファクラスの実装.
*/
#include"nkstdafx.h"
#include"nkConstantBuffer.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param initData	初期データ.
	* @param bufferSize	バッファサイズ.
	*/
	bool ConstantBuffer::Create(const void * initData, UINT bufferSize)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DEFAULT;	//バッファーで想定されている読み込みおよび書き込みの方法を識別.
		bd.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//16バイトアライメントに切りあげる。
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	//バッファーをどのようにパイプラインにバインドするかを識別.
		bd.CPUAccessFlags = 0;	//CPUアクセスのフラグ(CPUアクセスが必要でない場合は0).

		return IBuffer::Create(initData, bd);
	}

}