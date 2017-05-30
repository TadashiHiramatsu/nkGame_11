/**
* �����_�����O�R���e�L�X�g�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkRenderContext.h"

namespace nkEngine
{

	/**
	* ������.
	*
	* @param d3dDeviceContext	D3D�f�o�C�X�R���e�L�X�g.
	*/
	void RenderContext::Init(ID3D11DeviceContext * d3dDeviceContext)
	{
		//�f�o�C�X�R���e�L�X�g�̐ݒ�.
		D3DDeviceContext_ = d3dDeviceContext;
	}

	/**
	* �����_�����O�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[��ݒ�.
	* �[�x�X�e���V���r���[�͈�̂��̂��K�������.
	*
	* @param numView			�o�^���郌���_�����O�^�[�Q�b�g�N���X�̐�.
	* @param renderTarget		�o�^���郌���_�����O�^�[�Q�b�g�N���X.
	*/
	void RenderContext::OMSetRenderTarget(UINT numView, RenderTarget* renderTarget)
	{
		//�����_�����O�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[�̐ݒ�.
		ZeroMemory(RenderTargetViewList_, sizeof(RenderTargetViewList_));
		DepthStencilView_ = renderTarget[0].GetDepthStencilView();
		for (UINT i = 0; i < numView; i++)
		{
			RenderTargetViewList_[i] = renderTarget[0].GetRenderTargetView();
		}
		D3DDeviceContext_->OMSetRenderTargets(numView, RenderTargetViewList_, DepthStencilView_);
		NumRenderTargetView_ = numView;
	}

}