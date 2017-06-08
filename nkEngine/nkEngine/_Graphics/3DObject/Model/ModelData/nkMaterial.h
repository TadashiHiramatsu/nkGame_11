/**
* �}�e���A���N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �}�e���A���N���X.
	*/
	class Material : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Material()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~Material()
		{
		}

		/**
		* ������. 
		*/
		void Init(string textureName);

		/**
		* �e�N�X�`����SRV���擾.
		*/
		ShaderResourceView& GetTextureSRV()
		{
			return Texture_.GetTextureSRV();
		}

		/**
		* �@���}�b�v�̗L�����擾.
		*/
		bool isNormalMap()
		{
			if (NormalTexture_ != nullptr)
			{
				return true;
			}
			return false;
		}

		/**
		* �@���}�b�v�e�N�X�`����SRV���擾.
		*/
		ShaderResourceView& GetNormalTextureSRV()
		{
			if (NormalTexture_ != nullptr)
			{
				return NormalTexture_->GetTextureSRV();
			}
		}

		/**
		* �X�y�L�����}�b�v�̗L�����擾.
		*/
		bool isSpecularMap()
		{
			if (SpecularTexture_ != nullptr)
			{
				return true;
			}
			return false;
		}

		/**
		* �X�y�L�����}�b�v�e�N�X�`����SRV���擾.
		*/
		ShaderResourceView& GetSpecularTextureSRV()
		{
			if (SpecularTexture_ != nullptr)
			{
				return SpecularTexture_->GetTextureSRV();
			}
		}

	public:

		/** �e�N�X�`����. */
		string TextureName_ = "";

		/** �e�N�X�`��. */
		Texture Texture_;

		/** �@���}�b�v�e�N�X�`��. */
		Texture* NormalTexture_ = nullptr;
		/** �X�y�L�����}�b�v�e�N�X�`��. */
		Texture* SpecularTexture_ = nullptr;

	};

}