/**
* �C���f�b�N�X�o�b�t�@�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkIndexBuffer.h"

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param srcIndexBuffer	�\�[�X�C���f�b�N�X�o�b�t�@.
	* @param indexNum		�C���f�b�N�X��.
	*/
	bool IndexBuffer::Create(const void * srcIndexBuffer, UINT indexNum)
	{
		//�C���f�b�N�X�o�b�t�@�쐬
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