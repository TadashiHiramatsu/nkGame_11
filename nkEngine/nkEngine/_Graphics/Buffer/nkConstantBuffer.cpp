/**
* �萔�o�b�t�@�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkConstantBuffer.h"

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param initData	�����f�[�^.
	* @param bufferSize	�o�b�t�@�T�C�Y.
	*/
	bool ConstantBuffer::Create(const void * initData, UINT bufferSize)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DEFAULT;	//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@������.
		bd.ByteWidth = (((bufferSize - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	//�o�b�t�@�[���ǂ̂悤�Ƀp�C�v���C���Ƀo�C���h���邩������.
		bd.CPUAccessFlags = 0;	//CPU�A�N�Z�X�̃t���O(CPU�A�N�Z�X���K�v�łȂ��ꍇ��0).

		return IBuffer::Create(initData, bd);
	}

}