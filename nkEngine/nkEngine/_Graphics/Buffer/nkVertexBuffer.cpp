/**
* ���_�o�b�t�@�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkVertexBuffer.h"

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param srcVertexBuffer	�\�[�X���_�o�b�t�@.
	* @param numVertex			���_��.
	* @param stride				���_�X�g���C�h.
	*/
	bool VertexBuffer::Create(const void * srcVertexBuffer, int numVertex, int stride)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DEFAULT;	//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@������.
		bd.ByteWidth = stride * numVertex;	//�o�b�t�@�̃T�C�Y(�o�C�g�P��).
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//�o�b�t�@�[���ǂ̂悤�Ƀp�C�v���C���Ƀo�C���h���邩������.
		bd.CPUAccessFlags = 0;	//CPU�A�N�Z�X�̃t���O(CPU�A�N�Z�X���K�v�łȂ��ꍇ��0).

		//�X�g���C�h�̐ݒ�.
		Stride_ = stride;
		
		return IBuffer::Create(srcVertexBuffer, bd);
	}

}