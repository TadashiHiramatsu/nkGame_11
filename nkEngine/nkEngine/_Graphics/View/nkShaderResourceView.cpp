/**
* �V�F�[�_���\�[�X�r���[�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkShaderResourceView.h"

namespace nkEngine
{

	/**
	* �e�N�X�`���p��SRV���쐬.
	*
	* @param texture	�e�N�X�`��.
	*/
	bool ShaderResourceView::Create(ID3D11Texture2D * texture)
	{
		//���.
		Release();

		if (texture != nullptr)
		{
			//�e�N�X�`���̐ݒ�.
			D3D11_TEXTURE2D_DESC td;
			texture->GetDesc(&td);

			//�V�F�[�_���\�[�X�r���[�̐ݒ�.
			D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
			ZeroMemory(&srvd, sizeof(srvd));

			srvd.Format = td.Format;	//�t�H�[�}�b�g.
			srvd.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;	//�r���[�̃��\�[�X�^�C�v.
			srvd.Texture2D.MipLevels = td.MipLevels;	//�~�b�v�}�b�v���x��.

			HRESULT hr = Engine().GetDevice()->CreateShaderResourceView(texture, &srvd, &D3DSRV_);
			if (FAILED(hr))
			{
				//�쐬�s��.
				return false;
			}
		}
		else
		{
			//�e�N�X�`���Ȃ�.
			return false;
		}

		//����I��.
		return true;
	}

	/**
	* ���.
	* �f�X�g���N�^�ŌĂ�ł���.
	*/
	void ShaderResourceView::Release()
	{
		if (D3DSRV_ != nullptr)
		{
			D3DSRV_->Release();
			D3DSRV_ = nullptr;
		}
	}

}