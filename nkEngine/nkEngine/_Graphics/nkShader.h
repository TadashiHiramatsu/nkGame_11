/**
* �V�F�[�_�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �V�F�[�_�N���X.
	*/
	class Shader : Noncopyable
	{
	public:

		/**
		* �V�F�[�_�^�C�v.
		*/
		enum class TypeE
		{
			NONE = -1,	//!< ���ǂݍ���.
			VS,			//!< ���_�V�F�[�_.
			PS,			//!< �s�N�Z���V�F�[�_.
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		Shader()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~Shader() 
		{
			Release();
		}

		/**
		* �ǂݍ���.
		*
		* @param fileName	�t�@�C����.
		* @param entryName	�G���g���[�|�C���^�ƂȂ�֐��̖��O.
		* @param type		�V�F�[�_�^�C�v.
		*/
		bool Load(string fileName, const char* entryName, TypeE type);

		/**
		* ���.
		*/
		void Release();

		/**
		* �V�F�[�_�̎擾.
		*/
		void* GetBody()
		{
			return Shader_;
		}

		/**
		* �C���v�b�g���C�A�E�g�̎擾.
		*/
		ID3D11InputLayout* GetInputLayout()
		{
			return InputLayout_;
		}

	private:

		/**
		* �t�@�C���̓ǂݍ���.
		*
		* @param filePath	�t�@�C���p�X.
		* @param readBuffer	�ǂݍ��ݐ�o�b�t�@.
		* @param fileSize	�t�@�C���T�C�Y.
		*/
		void ReadFile(const char* filePath, char* readBuffer, int& fileSize);

		/**
		* ���_�V�F�[�_�[���璸�_���C�A�E�g�𐶐�.
		*
		* @param pShaderBlob	�R���p�C���ς݃V�F�[�_�ւ̃|�C���^.
		* @param pInputLayout	�C���v�b�g���C�A�E�g�̏o�͐�.
		*/
		HRESULT CreateInputLayout(ID3DBlob* pShaderBlob, ID3D11InputLayout** pInputLayout);

	private:

		/** �V�F�[�_�^�C�v. */
		TypeE ShaderType_ = TypeE::NONE;
		/** �V�F�[�_. */
		void* Shader_ = nullptr;
		/** �C���v�b�g���C�A�E�g. */
		ID3D11InputLayout* InputLayout_ = nullptr;

	};
}