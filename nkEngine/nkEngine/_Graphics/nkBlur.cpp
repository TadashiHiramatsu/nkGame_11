/**
* �u���[�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkBlur.h"

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param w		��.
	* @param h		����.
	* @param srcSRV	���ƂȂ�SRV.
	*/
	void Blur::Create(int w, int h, ShaderResourceView & srcSRV)
	{
		//���ƂȂ�SRV.
		SrcSRV_ = &srcSRV;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
		SrcSRV_->GetBody()->GetDesc(&srvd);
	
		//�T�C�Y��ݒ�.
		SrcTexSize = Vector2(w, h);

		//�u���[�T�C�Y���쐬
		int  size[2][2]
		{
			{ w >> 1, h },
			{ w >> 1, h >> 1 },
		};

		//�}���`�����_�����O�̐ݒ�.
		DXGI_SAMPLE_DESC md;
		md.Count = 1;
		md.Quality = 0;
		//�����_�����O�^�[�Q�b�g�̍쐬
		for (int i = 0; i < 2; i++)
		{
			BlurRT_[i].Create(size[i][0], size[i][1], 1, srvd.Format, DXGI_FORMAT_D24_UNORM_S8_UINT, md);
		}

		static VertexBufferS vertex[] =
		{
			{ Vector4(-1.0f	, 1.0f	, 0.0f, 1.0f),Vector2(0.0f, 0.0f)},
			{ Vector4(1.0f	, 1.0f	, 0.0f, 1.0f),Vector2(1.0f, 0.0f)},
			{ Vector4(-1.0f	, -1.0f	, 0.0f, 1.0f),Vector2(0.0f, 1.0f)},
			{ Vector4(1.0f	, -1.0f	, 0.0f, 1.0f),Vector2(1.0f, 1.0f)},
		};

		VertexBuffer_.Create(vertex, 4, sizeof(VertexBufferS));

		//���_�V�F�[�_�[�����[�h�B
		VShaderXBlur_.Load("Blur", "VSBlur_X", Shader::TypeE::VS);
		VShaderYBlur_.Load("Blur", "VSBlur_Y", Shader::TypeE::VS);
		//�s�N�Z���V�F�[�_�[�����[�h�B
		PShader_.Load("Blur", "PSBlur", Shader::TypeE::PS);

		//VS�X�e�[�W�̒萔�o�b�t�@���쐬.
		VSConstantBuffer_.Create(nullptr, sizeof(VSConstantBufferS));

	}

	/**
	* �`��.
	*/
	void Blur::Render()
	{
		if (SrcSRV_ != nullptr)
		{
			//X�u���[.
			{
				//�����_�����O�^�[�Q�b�g��ݒ�.
				Engine().GetRenderContext().OMSetRenderTarget(1, &BlurRT_[0]);

				//�����_�����O�^�[�Q�b�g�r���[��0�Ԗڂ��N���A.
				float clearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
				Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
				Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);

				//�r���[�|�[�g��ݒ�B
				Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, BlurRT_[0].GetSize().x, BlurRT_[0].GetSize().y);

				//���_�o�b�t�@��ݒ�.
				Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);

				//�v���~�e�B�u�̃g�|���W�[��ݒ�.
				Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				//���_�V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().VSSetShader(VShaderXBlur_);
				//�s�N�Z���V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//���̓��C�A�E�g��ݒ�.
				Engine().GetRenderContext().IASetInputLayout(VShaderXBlur_.GetInputLayout());

				VSConstantBufferS vsConstant;
				vsConstant.TexSize_ = SrcTexSize;
				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//�e�N�X�`����ݒ�.
				Engine().GetRenderContext().PSSetShaderResource(0, *SrcSRV_);

				//�`��B
				Engine().GetRenderContext().Draw(4, 0);
			}
			//Y�u���[
			{
				//�����_�����O�^�[�Q�b�g��ݒ�.
				Engine().GetRenderContext().OMSetRenderTarget(1, &BlurRT_[1]);

				//�����_�����O�^�[�Q�b�g�r���[��0�Ԗڂ��N���A.
				float clearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
				Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
				Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);

				//�r���[�|�[�g��ݒ�B
				Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, BlurRT_[1].GetSize().x, BlurRT_[1].GetSize().y);

				//���_�o�b�t�@��ݒ�.
				Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);

				//�v���~�e�B�u�̃g�|���W�[��ݒ�.
				Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

				//���_�V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().VSSetShader(VShaderYBlur_);
				//�s�N�Z���V�F�[�_�[��ݒ�.
				Engine().GetRenderContext().PSSetShader(PShader_);
				//���̓��C�A�E�g��ݒ�.
				Engine().GetRenderContext().IASetInputLayout(VShaderYBlur_.GetInputLayout());

				VSConstantBufferS vsConstant;
				vsConstant.TexSize_ = BlurRT_[0].GetSize();
				//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
				Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
				//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
				Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

				//�e�N�X�`����ݒ�.
				Engine().GetRenderContext().PSSetShaderResource(0, BlurRT_[0].GetRenderTargetSRV());

				//�`��B
				Engine().GetRenderContext().Draw(4, 0);
			}
		}
	}

}