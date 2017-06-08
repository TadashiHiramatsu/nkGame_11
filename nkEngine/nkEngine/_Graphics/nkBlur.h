/**
* �u���[�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �u���[�N���X.
	*/
	class Blur : Noncopyable
	{
	public:

		/** 
		* ���_�o�b�t�@. 
		*/
		struct VertexBufferS
		{
			Vector4 Pos;	//!< ���W.
			Vector2 Tex;	//!< UV���W.
		};

		/**
		* VS�X�e�[�W�̒萔�o�b�t�@�\����.
		*/
		struct VSConstantBufferS
		{
			Vector2 TexSize_;	//!< �e�N�X�`���T�C�Y.
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		Blur()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~Blur()
		{
		}

		/**
		* �쐬.
		*
		* @param w		��.
		* @param h		����.
		* @param srcSRV	���ƂȂ�SRV.
		*/
		void Create(
			int w,
			int h,
			ShaderResourceView& srcSRV);

		/**
		* �`��.
		*/
		void Render();

		/**
		* �u���[���ʂ�SRV���擾.
		*/
		ShaderResourceView& GetBlurSRV()
		{
			return BlurRT_[1].GetRenderTargetSRV();
		}

	private:

		/** �u���[���ʂ��������ރ����_�����O�^�[�Q�b�g. */
		RenderTarget BlurRT_[2];

		/** ���ɂȂ�SRV. */
		ShaderResourceView* SrcSRV_ = nullptr;

		/** ���ƂȂ�e�N�X�`���̃T�C�Y. */
		Vector2 SrcTexSize = Vector2::Zero;

		/** X�u���[���_�V�F�[�_. */
		Shader VShaderXBlur_;
		/** Y�u���[���_�V�F�[�_. */
		Shader VShaderYBlur_;
		/** �s�N�Z���V�F�[�_. */
		Shader PShader_;

		/** ���_�o�b�t�@. */
		VertexBuffer VertexBuffer_;

		/** VS�X�e�[�W�̒萔�o�b�t�@. */
		ConstantBuffer VSConstantBuffer_;

	};

}