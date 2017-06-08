/**
* �T���v���X�e�[�g�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �T���v���X�e�[�g�N���X.
	*/
	class SamplerState : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		SamplerState()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~SamplerState()
		{
			Release();
		}

		/**
		* �쐬.
		*/
		bool Create(
			D3D11_TEXTURE_ADDRESS_MODE addressU,
			D3D11_TEXTURE_ADDRESS_MODE addressV
		);

		/**
		* ���.
		* �f�X�g���N�^�ŌĂ�ł��.
		*/
		void Release()
		{
			if (D3DSampler_ != nullptr)
			{
				D3DSampler_->Release();
				D3DSampler_ = nullptr;
			}
		}

		/**
		* D3D�T���v�����擾.
		*/
		ID3D11SamplerState* GetBody()
		{
			return D3DSampler_;
		}

	private:
		
		/** D3D�T���v���N���X. */
		ID3D11SamplerState* D3DSampler_ = nullptr;

	};

}