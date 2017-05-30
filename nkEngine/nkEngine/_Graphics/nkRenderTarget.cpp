/**
* �����_�����O�^�[�Q�b�g�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkRenderTarget.h"

namespace nkEngine
{

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
	bool RenderTarget::Create(
		int w, 
		int h,	
		int mipLevel,
		DXGI_FORMAT colorFormat,
		DXGI_FORMAT depthStencilFormat,
		DXGI_SAMPLE_DESC multiSampleDesc)
	{
		HRESULT hr = E_FAIL;

		Size_ = Vector2(w, h);

		//�����_�����O�^�[�Q�b�g�̍쐬�B
		D3D11_TEXTURE2D_DESC td;
		ZeroMemory(&td, sizeof(td));

		td.Width = w;	//��.
		td.Height = h;	//����.
		td.MipLevels = mipLevel;	//�~�b�v���x��.
		td.ArraySize = 1;	//�e�N�X�`���z����̃e�N�X�`���̐�.
		td.Format = colorFormat;	//�t�H�[�}�b�g.
		td.SampleDesc = multiSampleDesc;	//�}���`�T���v�����O�p�����[�^.
		td.Usage = D3D11_USAGE_DEFAULT;		//�ǂݍ��ݏ������ݐݒ�.
		td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;	//�o�C���h�t���O.
		td.CPUAccessFlags = 0;	//CPU�T�N�Z�X�t���O(0:�A�N�Z�X�s�v).
		td.MiscFlags = 0;	//���̈�ʐ��̒Ⴂ���\�[�X�I�v�V����(0:�g�p���Ȃ�).

		hr = Engine().GetDevice()->CreateTexture2D(&td, nullptr, &D3DRenderTargetTexture_);
		if (FAILED(hr)) 
		{
			//�����_�����O�^�[�Q�b�g�̍쐬�Ɏ��s.
			return false;
		}

		//�����_�����O�^�[�Q�b�g�r���[���쐬.
		hr = Engine().GetDevice()->CreateRenderTargetView(D3DRenderTargetTexture_, nullptr, &D3DRenderTargetView_);
		if (FAILED(hr))
		{
			//�����_�����O�^�[�Q�b�g�r���[���쐬�o���Ȃ�����.
			return false;
		}

		RenderTargetSRV_.Create(D3DRenderTargetTexture_);

		if (depthStencilFormat != DXGI_FORMAT_UNKNOWN)
		{
			//�쐬.
			
			//�[�x�X�e���V���e�N�X�`���̍쐬.
			td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

			hr = Engine().GetDevice()->CreateTexture2D(&td, NULL, &D3DDepthStencilTexture_);
			if (FAILED(hr))
			{
				return false;
			}

			//�[�x�X�e���V���r���[�̍쐬.
			D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
			ZeroMemory(&descDSV, sizeof(descDSV));
			descDSV.Format = td.Format;
			descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
			descDSV.Texture2D.MipSlice = 0;
			hr = Engine().GetDevice()->CreateDepthStencilView(D3DDepthStencilTexture_, &descDSV, &D3DDepthStencilView_);
			if (FAILED(hr))
			{
				return false;
			}

		}

		return true;

	}

	/**
	* ���.
	*/
	void RenderTarget::Release()
	{
		if (D3DRenderTargetTexture_ != nullptr)
		{
			D3DRenderTargetTexture_->Release();
			D3DRenderTargetTexture_ = nullptr;
		}
		if (D3DRenderTargetView_ != nullptr)
		{
			D3DRenderTargetView_->Release();
			D3DRenderTargetView_ = nullptr;
		}
		if (D3DDepthStencilTexture_ != nullptr)
		{
			D3DDepthStencilTexture_->Release();
			D3DDepthStencilTexture_ = nullptr;
		}
		if (D3DDepthStencilView_ != nullptr)
		{
			D3DDepthStencilView_->Release();
			D3DDepthStencilView_ = nullptr;
		}
	}

}