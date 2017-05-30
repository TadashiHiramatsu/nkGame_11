/**
* ���_�o�b�t�@�N���X�̒�`.
*/
#pragma once

#include"nkBuffer.h"

namespace nkEngine
{

	/**
	* ���_�o�b�t�@�N���X.
	*/
	class VertexBuffer : public IBuffer
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		VertexBuffer()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~VertexBuffer()
		{
		}

		/**
		* �쐬.
		*
		* @param srcVertexBuffer	�\�[�X���_�o�b�t�@.
		* @param numVertex	���_��.
		* @param stride		���_�X�g���C�h.
		*/
		bool Create(const void* srcVertexBuffer, int numVertex, int stride);

		/**
		* ���_�X�g���C�h�̎擾.
		*/
		int GetStride() const
		{
			return Stride_;
		}

	private:
		
		/** ���_�X�g���C�h. */
		int Stride_ = 0;

	};

}