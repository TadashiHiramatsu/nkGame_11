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
			RenderTargetViewList_[i] = renderTarget[i].GetRenderTargetView();
		}
		D3DDeviceContext_->OMSetRenderTargets(numView, RenderTargetViewList_, DepthStencilView_);
		NumRenderTargetView_ = numView;
	}

	/**
	* PS�X�e�[�W�ɃT���v���X�e�[�g��ݒ�.
	*
	* @param startSlot		�J�n�X���b�g�ԍ�.
	* @param numSamplers	�T���v����.
	* @param sampler		�T���v���X�e�[�g�N���X.
	*/
	void RenderContext::PSSetSampler(UINT startSlot, UINT numSamplers, SamplerState * sampler)
	{
		ZeroMemory(D3DSamplerList_, sizeof(D3DSamplerList_));

		for (int i = 0; i < numSamplers; i++)
		{
			D3DSamplerList_[i] = sampler[0].GetBody();
		}
		D3DDeviceContext_->PSSetSamplers(startSlot, numSamplers, D3DSamplerList_);
	}

}