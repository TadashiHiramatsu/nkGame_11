/**
* �C���f�b�N�X�o�b�t�@�N���X�̒�`.
*/
#pragma once

#include"_Graphics\Buffer\nkBuffer.h"

namespace nkEngine
{

	/**
	* �C���f�b�N�X�o�b�t�@�N���X.
	*/
	class IndexBuffer : public IBuffer
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		IndexBuffer()
		{
		}
		
		/**
		* �f�X�g���N�^.
		*/
		~IndexBuffer()
		{
		}

		/**
		* �쐬.
		*
		* @param srcIndexBuffer	�\�[�X�C���f�b�N�X�o�b�t�@.
		* @param indexNum		�C���f�b�N�X��.
		*/
		bool Create(const void* srcIndexBuffer, UINT indexNum);

	private:

	};
}