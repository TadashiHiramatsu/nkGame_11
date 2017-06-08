/**
* �V�F�[�_���\�[�X�r���[�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �V�F�[�_���\�[�X�r���[�N���X.
	* �A�_�v�^�[�p�^�[��?�N���X.
	*/
	class ShaderResourceView : Noncopyable 
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		ShaderResourceView()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~ShaderResourceView()
		{
			//���.
			Release();
		}

		/**
		* �e�N�X�`���p��SRV���쐬.
		*
		* @param texture	�e�N�X�`��.
		*/
		bool Create(ID3D11Texture2D* texture);

		/**
		* �e�N�X�`���p��SRV���쐬.
		*
		* @param meta	�e�N�X�`�����^�f�[�^.
		* @param image	�X�N���b�`�C���[�W.
		*/
		bool Create(DirectX::TexMetadata& meta, DirectX::ScratchImage& image);

		/**
		* ���.
		* �f�X�g���N�^�ŌĂ�ł���.
		*/
		void Release();

		/**
		* ID3D11ShaderResourceView���擾.
		*/
		ID3D11ShaderResourceView*& GetBody()
		{
			return D3DSRV_;
		}

	private:

		/** D3D11��SRV�N���X. */
		ID3D11ShaderResourceView* D3DSRV_ = nullptr;

	};

}