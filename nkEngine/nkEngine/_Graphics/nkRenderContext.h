/**
* �����_�����O�R���e�L�X�g�N���X�̒�`.
*/
#pragma once

#include"nkShader.h"
#include"Buffer\nkVertexBuffer.h"
#include"Buffer\nkIndexBuffer.h"
#include"Buffer\nkConstantBuffer.h"

#include"_Graphics\nkRenderTarget.h"

namespace nkEngine
{

	/**
	* �����_�����O�R���e�L�X�g�N���X.
	* �o�b�t�@�ւ̃����_�����O���s��.
	*/
	class RenderContext : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		RenderContext()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~RenderContext()
		{
		}

		/**
		* ������.
		* �ݒ肵��D3D�f�o�C�X�R���e�L�X�g�͏��������ŉ������.
		*
		* @param d3dDeviceContext	D3D�f�o�C�X�R���e�L�X�g.
		*/
		void Init(ID3D11DeviceContext* d3dDeviceContext);

		/**
		* �����_�����O�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[��ݒ�.
		* �[�x�X�e���V���r���[�͈�̂��̂��K�������.
		*
		* @param numView			�o�^���郌���_�����O�^�[�Q�b�g�N���X�̐�.
		* @param renderTarget		�o�^���郌���_�����O�^�[�Q�b�g�N���X.
		*/
		void OMSetRenderTarget(UINT numView, RenderTarget* renderTarget);

		/**
		* �r���[�|�[�g�̐ݒ�.
		*
		* @param topLeftX	�r���[�|�[�g�̍����X���W.
		* @param topLeftY	�r���[�|�[�g�̍����Y���W.
		* @param width		�r���[�|�[�g�̕�.
		* @param heigth		�r���[�|�[�g�̍���.
		*/
		void RSSetViewport(float topLeftX, float topLeftY, float width, float heigth)
		{
			Viewport_.Width = width;
			Viewport_.Height = heigth;
			Viewport_.TopLeftX = topLeftX;
			Viewport_.TopLeftY = topLeftY;
			Viewport_.MinDepth = 0.0f;
			Viewport_.MaxDepth = 1.0f;
			D3DDeviceContext_->RSSetViewports(1, &Viewport_);
		}

		/**
		* �����_�����O�^�[�Q�b�g�r���[���N���A.
		*
		* @param rtNo		�����_�����O�^�[�Q�b�g�r���[�̔ԍ�.
		* @param clearColor	�N���A�J���[.		
		*/
		void ClearRenderTargetView(UINT rtNo, float* clearColor)
		{
			if (rtNo < NumRenderTargetView_ && RenderTargetViewList_[rtNo] != nullptr)
			{
				//�����_�����O�^�[�Q�b�g�r���[�̔ԍ������݂��Ă���
				//�������_�����O�^�[�Q�b�g���ݒ肳��Ă���.
				D3DDeviceContext_->ClearRenderTargetView(RenderTargetViewList_[rtNo], clearColor);
			}
		}

		/**
		* �[�x�X�e���V���r���[�̃N���A.
		*
		* @param clearFlag	�N���A�t���O(D3D11_CLEAR_FLAG�񋓌^).
		*/
		void ClearDepthStencilView(UINT clearFlag)
		{
			if (DepthStencilView_ != nullptr)
			{
				D3DDeviceContext_->ClearDepthStencilView(DepthStencilView_, clearFlag, 1.0f, 0);
			}
		}

		/**
		* ���_�o�b�t�@��ݒ�.
		*
		* @param vertexBuffer	���_�o�b�t�@.
		*/
		void IASetVertexBuffer(VertexBuffer& vertexBuffer)
		{
			UINT offset = 0;
			UINT stride = vertexBuffer.GetStride();
			D3DDeviceContext_->IASetVertexBuffers(
				0,	//�g���n�߂̃X���b�g�ԍ�.
				1,	//���_�o�b�t�@�z��̗v�f��.
				&vertexBuffer.GetBody(),	//���_�o�b�t�@.
				&stride,	//���_�o�b�t�@�[�Ŏg�p�����v�f�̃T�C�Y.
				&offset	//���_���̑O�Ƀw�b�_��񂪂���ꍇ�ς�����ۂ�.
			);
		}

		/**
		* �C���f�b�N�X�o�b�t�@��ݒ�.
		*
		* @param indexBuffer	�C���f�b�N�X�o�b�t�@.
		* @param format			�t�H�[�}�b�g.
		*/
		void IASetIndexBuffer(IndexBuffer& indexBuffer, DXGI_FORMAT format)
		{
			UINT offset = 0;
			D3DDeviceContext_->IASetIndexBuffer(indexBuffer.GetBody(), format, offset);
		}

		/**
		* �v���~�e�B�u�̃g�|���W�[��ݒ�.
		*
		* @param topology	�g�|���W�[.
		*/
		void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
		{
			D3DDeviceContext_->IASetPrimitiveTopology(topology);
		}

		/**
		* ���_�V�F�[�_��ݒ�.
		*
		* @param shader	���_�V�F�[�_.
		*/
		void VSSetShader(Shader& shader)
		{
			D3DDeviceContext_->VSSetShader((ID3D11VertexShader*)shader.GetBody(), nullptr, 0);
		}

		/**
		* �s�N�Z���V�F�[�_��ݒ�.
		*
		* @param shader	�s�N�Z���V�F�[�_.
		*/
		void PSSetShader(Shader& shader)
		{
			D3DDeviceContext_->PSSetShader((ID3D11PixelShader*)shader.GetBody(), nullptr, 0);
		}

		/**
		* �`��.
		*
		* @param vertexCount			���_��.
		* @param startVertexLocation	�`����J�n���钸�_�̈ʒu�B���0�ő��v.
		*/
		void Draw(UINT vertexCount,UINT startVertexLocation)
		{
			D3DDeviceContext_->Draw(vertexCount, startVertexLocation);
		}

		/**
		* �`��.
		*
		* @param IndexCount	�C���f�b�N�X��.
		* @param StartIndexLocation	.
		* @param BaseVertexLocation	.
		*/
		void DrawIndexed(UINT IndexCount,UINT StartIndexLocation,INT BaseVertexLocation)
		{
			D3DDeviceContext_->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
		}

		/**
		* ���̓��C�A�E�g��ݒ�.
		*
		* @param inputLayout	���̓��C�A�E�g.
		*/
		void IASetInputLayout(ID3D11InputLayout* inputLayout)
		{
			D3DDeviceContext_->IASetInputLayout(inputLayout);
		}

		/**
		* VS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�.
		*
		* @param slotNo	�X���b�g�ԍ�.
		* @param cb		�萔�o�b�t�@.
		*/
		void VSSetConstantBuffer(UINT slotNo, ConstantBuffer& cb)
		{
			D3DDeviceContext_->VSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}

		/**
		* PS�X�e�[�W�ɒ萔�o�b�t�@��ݒ�.
		*
		* @param slotNo	�X���b�g�ԍ�.
		* @param cb		�萔�o�b�t�@.
		*/
		void PSSetConstantBuffer(UINT slotNo, ConstantBuffer& cb)
		{
			D3DDeviceContext_->PSSetConstantBuffers(slotNo, 1, &cb.GetBody());
		}

		/**
		* ���_�V�F�[�_��SRV��ݒ�.
		*
		* @param slotNo	�X���b�g�ԍ�.
		* @param srv	�V�F�[�_���\�[�X�r���[.
		*/
		void VSSetShaderResource(int slotNo, ShaderResourceView& srv)
		{
			D3DDeviceContext_->VSSetShaderResources(slotNo, 1, &srv.GetBody());
		}

		/**
		* �s�N�Z���V�F�[�_��SRV��ݒ�.
		*
		* @param slotNo	�X���b�g�ԍ�.
		* @param srv	�V�F�[�_���\�[�X�r���[.
		*/
		void PSSetShaderResource(int slotNo, ShaderResourceView& srv)
		{
			D3DDeviceContext_->PSSetShaderResources(slotNo, 1, &srv.GetBody());
		}

		/**
		* �T�u���\�[�X���X�V.
		*
		* @param & buffer		�R�s�[��o�b�t�@.
		* @param & srcBuffer	�\�[�X�o�b�t�@.
		*/
		template<class TBuffer, class SrcBuffer>
		void UpdateSubresource(TBuffer& buffer, const SrcBuffer& srcBuffer)
		{
			if (buffer.GetBody() != nullptr) 
			{
				D3DDeviceContext_->UpdateSubresource(buffer.GetBody(), 0, nullptr, &srcBuffer, 0, 0);
			}
		}

		/**
		* ���\�[�X���R�s�[.
		*
		* @param destRes	�R�s�[��.
		* @param srcRes	�R�s�[��.
		*/
		template<class TResource>
		void CopyResource(TResource& destRes, TResource& srcRes)
		{
			if (destRes.GetBody() != nullptr&& srcRes.GetBody() != nullptr)
			{
				D3DDeviceContext_->CopyResource(destRes.GetBody(), srcRes.GetBody());
			}
		}
		/**
		* ���\�[�X���R�s�[.
		*
		* @param destRes	�R�s�[��.
		* @param srcRes	�R�s�[��.
		*/
		void CopyResource(ID3D11Resource* destRes, ID3D11Resource* srcRes)
		{
			if (destRes != nullptr&& srcRes != nullptr)
			{
				D3DDeviceContext_->CopyResource(destRes, srcRes);
			}
		}

	private:

		static const int MRT_MAX = 8;	//MRT�̍ő吔.

		/** D3D�f�o�C�X�R���e�L�X�g. */
		ID3D11DeviceContext* D3DDeviceContext_ = nullptr;
		/** �r���[�|�[�g. */
		D3D11_VIEWPORT Viewport_;
		/** 
		* ���ݎg�p����Ă��郌���_�����O�^�[�Q�b�g�r���[. 
		* �����ݒ肵����}���`�����_�����O�ł���̂��ȁH.
		* �X���b�v�`�F�C���̏��������ς��Ȃ��Ⴂ���Ȃ�����.
		*/
		ID3D11RenderTargetView* RenderTargetViewList_[MRT_MAX] = { nullptr };
		/** ���ݐݒ肳��Ă���[�x�X�e���V���r���[. */
		ID3D11DepthStencilView* DepthStencilView_ = nullptr;
		/** �����_�����O�^�[�Q�b�g�r���[�̐�. */
		UINT NumRenderTargetView_ = 0;
	
	};
}