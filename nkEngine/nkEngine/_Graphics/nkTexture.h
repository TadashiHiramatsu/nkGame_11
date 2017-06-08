/**
* �e�N�X�`���N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �e�N�X�`���N���X.
	*/
	class Texture : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Texture()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~Texture()
		{
		}

		/**
		* �ǂݍ���.
		*
		* @param fileName	�t�@�C����.
		*/
		bool Load(string fileName);

		/**
		* �e�N�X�`����SRV���擾.
		*/
		ShaderResourceView& GetTextureSRV()
		{
			return TextureSRV_;
		}

	private:

		/** �e�N�X�`�����^�f�[�^. */
		DirectX::TexMetadata DXTexMetaData_;
		/** */
		DirectX::ScratchImage DXScratchImage_;
		/** �e�N�X�`����SRV. */
		ShaderResourceView TextureSRV_;

	};

}