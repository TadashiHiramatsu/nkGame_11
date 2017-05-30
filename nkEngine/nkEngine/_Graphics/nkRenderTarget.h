/**
* �����_�����O�^�[�Q�b�g�N���X�̒�`.
*/
#pragma once

#include"View\nkShaderResourceView.h"

namespace nkEngine
{

	/**
	* �����_�����O�^�[�Q�b�g�N���X.
	*/
	class RenderTarget : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		RenderTarget()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~RenderTarget()
		{
			Release();
		}

		/**
		* �쐬.
		*
		* @param w						��.
		* @param h						����.
		* @param mipLevel				�~�b�v�}�b�v���x��.
		* @param colorFormat			�J���[�o�b�t�@�̃t�H�[�}�b�g.
		* @param depthStencilFormat		�[�x�X�e���V���o�b�t�@�̃t�H�[�}�b�g.
		* @param multiSampleDesc		�}���`�T���v�����O�̒�`.
		*/
		bool Create(
			int w, 
			int h, 
			int mipLevel, 
			DXGI_FORMAT colorFormat,
			DXGI_FORMAT depthStencilFormat,
			DXGI_SAMPLE_DESC multiSampleDesc
		);

		/**
		* ���. 
		*/
		void Release();

		/**
		* �����_�����O�^�[�Q�b�g���擾.
		*/
		ID3D11Texture2D* GetRenderTarget()
		{
			return D3DRenderTargetTexture_;
		}

		/**
		* �����_�����O�^�[�Q�b�g�r���[���擾.
		*/
		ID3D11RenderTargetView* GetRenderTargetView()
		{
			return D3DRenderTargetView_;
		}

		/**
		* �[�x�X�e���V���r���[���擾.
		*/
		ID3D11DepthStencilView* GetDepthStencilView()
		{
			return D3DDepthStencilView_;
		}

		/**
		* �����_�����O�^�[�Q�b�g�pSRV���擾.
		*/
		ShaderResourceView& GetRenderTargetSRV()
		{
			return RenderTargetSRV_;
		}

		/**
		* �T�C�Y�̎擾.
		*/
		const Vector2& GetSize()
		{
			return Size_;
		}

	private:

		/** �����_�����O�^�[�Q�b�g�e�N�X�`��. */
		ID3D11Texture2D* D3DRenderTargetTexture_ = nullptr;
		/** �����_�����O�^�[�Q�b�g. */
		ID3D11RenderTargetView*	D3DRenderTargetView_ = nullptr;
		/** �����_�����O�^�[�Q�b�g�pSRV. */
		ShaderResourceView RenderTargetSRV_;
		/** �[�x�X�e���V���e�N�X�`��. */
		ID3D11Texture2D* D3DDepthStencilTexture_ = nullptr;
		/** �[�x�X�e���V���r���[. */
		ID3D11DepthStencilView* D3DDepthStencilView_ = nullptr;

		/** �����_�����O�^�[�Q�b�g�̃T�C�Y. */
		Vector2 Size_ = Vector2::Zero;
	
	};

}