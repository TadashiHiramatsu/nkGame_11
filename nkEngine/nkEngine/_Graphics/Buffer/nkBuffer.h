/**
* �o�b�t�@�̊��N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �o�b�t�@�̊��N���X.
	*/
	class IBuffer : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		IBuffer()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~IBuffer()
		{
		}

		/**
		* �쐬.
		*
		* @param initData	�����f�[�^.
		* @param bufferDesc	�o�b�t�@��`.
		*/
		bool Create(const void* initData, D3D11_BUFFER_DESC& bufferDesc);

		/**
		* ���.
		*/
		void Release();

		/**
		* ID3D11Buffer*�擾.
		*/
		ID3D11Buffer*& GetBody()
		{
			return D3DBuffer_;
		}

	protected:

		/** �o�b�t�@. */
		ID3D11Buffer* D3DBuffer_ = nullptr;

	};

}