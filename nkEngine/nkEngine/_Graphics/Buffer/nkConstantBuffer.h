/**
* �萔�o�b�t�@�N���X�̒�`.
*/
#pragma once

#include"nkBuffer.h"

namespace nkEngine
{

	/**
	* �萔�o�b�t�@�N���X.
	*/
	class ConstantBuffer : public IBuffer
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		ConstantBuffer()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~ConstantBuffer()
		{
		}

		/**
		* �쐬.
		*
		* @param initData	�����f�[�^.
		* @param bufferSize	�o�b�t�@�T�C�Y.
		*/
		bool Create(const void* initData, UINT bufferSize);

	private:

	};

}