/**
* �`��̊��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkShape.h"

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param transform	�g�����X�t�H�[���̃|�C���^.
	* @param light		���C�g�̃|�C���^.
	* @param camera		�J�����̃|�C���^.
	*/
	void IShape::Create(Transform * transform, Light * light, Camera * camera)
	{
		Transform_ = transform;
		Light_ = light;
		Camera_ = camera;

		//���_�V�F�[�_�[�����[�h�B
		VShader_.Load("Shape", "VSShape", Shader::TypeE::VS);
		//�s�N�Z���V�F�[�_�[�����[�h�B
		PShader_.Load("Shape", "PSShape", Shader::TypeE::PS);

		CreateBuffer();

	}

	/**
	* �`��.
	*/
	void IShape::Render()
	{

		//���_�o�b�t�@��ݒ�.
		Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);
		//�C���f�b�N�X�o�b�t�@��ݒ�.
		Engine().GetRenderContext().IASetIndexBuffer(IndexBuffer_, DXGI_FORMAT_R16_UINT);

		//�v���~�e�B�u�̃g�|���W�[��ݒ�.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//���_�V�F�[�_�[��ݒ�.
		Engine().GetRenderContext().VSSetShader(VShader_);
		//�s�N�Z���V�F�[�_�[��ݒ�.
		Engine().GetRenderContext().PSSetShader(PShader_);
		//���̓��C�A�E�g��ݒ�.
		Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

		VSConstantBufferS vsConstant;
		vsConstant.WorldMatrix_ = Transform_->WorldMatrix_;
		vsConstant.ViewMatrix_ = Camera_->GetViewMatrix();
		vsConstant.ProjMatrix_ = Camera_->GetProjectionMatrix();
		//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
		Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
		//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
		Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

		PSConstantBufferS psConstant;
		psConstant.Light_ = *Light_;
		//VS�X�e�[�W�̒萔�o�b�t�@���X�V.
		Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
		//VS�X�e�[�W�̒萔�o�b�t�@��ݒ�.
		Engine().GetRenderContext().PSSetConstantBuffer(1, PSConstantBuffer_);

		//�`��B
		Engine().GetRenderContext().DrawIndexed(36, 0, 0);

	}

	/**
	* �o�b�t�@�̍쐬.
	*/
	void IShape::CreateBuffer()
	{
		//VS�X�e�[�W�̒萔�o�b�t�@���쐬.
		VSConstantBuffer_.Create(nullptr, sizeof(VSConstantBufferS));
		//PS�X�e�[�W�̒萔�o�b�t�@���쐬.
		PSConstantBuffer_.Create(nullptr, sizeof(PSConstantBufferS));
	}

}