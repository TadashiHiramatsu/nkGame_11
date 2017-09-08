/**
* ���f���`��N���X�̒�`.
*/
#pragma once

#include"nkModelData.h"
#include"_Object\Component\nkComponent.h"

namespace nkEngine
{

	/**
	* ���f���`��N���X.
	*/
	class ModelRender : public IComponent
	{
	public:

		enum ShaderResourceCodeE
		{
			DiffuseTexture = 0,	//!< �f�B�t���[�Y�e�N�X�`��.
			NormalTexture,		//!< �@���e�N�X�`��.
			SpecularTexture,	//!< �X�y�L�����e�N�X�`��.
			ShadowTexture,		//!< �e�e�N�X�`��.
		};

		/**
		* VS�X�e�[�W�̒萔�o�b�t�@�\����.
		*/
		struct VSConstantBufferS
		{
			Matrix WorldMatrix_;	//!< ���[���h�s��.
			Matrix ViewMatrix_;		//!< �r���[�s��.
			Matrix ProjMatrix_;		//!< �v���W�F�N�V�����s��.
		};

		/**
		* PS�X�e�[�W�̒萔�o�b�t�@�\����.
		*/
		struct PSConstantBufferS
		{
			Light Light_;	//!< ���C�g.
			ShadowMap::ShadowReceiverParamS SRP_;	//!< �V���h�E���V�[�o�[�p�p�����[�^.
			Vector4 CameraPos_;	//!< �J�����|�W�V����.
			Vector4 CameraDir_;	//!< �J�����̎���.
			Vector4 EffectFlag_ = Vector4::Zero;	//!< x:�@���}�b�v, y:�X�y�L�����}�b�v, z:�������C�g.
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		ModelRender(IGameObject* go) : 
			IComponent(go)
		{
			Name_ = "ModelRender";
		}

		/**
		* �f�X�g���N�^.
		*/
		~ModelRender()
		{
		}

		/**
		* ������.
		*/
		void Start(
			Light* light,
			Camera* camera
		);

		/**
		* Render�O�̕`��.
		*/
		void PreRender()override;

		/**
		* �`��.
		*/
		void Render()override;

		/**
		* �V���h�E�}�b�v�`��.
		*/
		void RenderToShadowMap();

		/**
		* �������C�g�t���O��ݒ肷��.
		*/
		void SetLimLight(bool lim)
		{
			IsLimLight_ = lim;
		}

	private:

		/** ���f���f�[�^. */
		ModelData* ModelData_ = nullptr;

		/** �g�����X�t�H�[��. */
		Transform* Transform_ = nullptr;

		/** ���_�V�F�[�_. */
		Shader VShader_;
		/** �X�L���p���_�V�F�[�_. */
		Shader SkinVShader_;
		/** �s�N�Z���V�F�[�_. */
		Shader PShader_;

		/** VS�X�e�[�W�̒萔�o�b�t�@. */
		ConstantBuffer VSConstantBuffer_;
		/** PS�X�e�[�W�̒萔�o�b�t�@. */
		ConstantBuffer PSConstantBuffer_;

		/** �T���v���X�e�[�g. */
		SamplerState SamplerState_;

		/** ���C�g�̃|�C���^. */
		Light* Light_ = nullptr;
		/** �J�����̃|�C���^. */
		Camera* Camera_ = nullptr;

		/** �������C�g�t���O. */
		bool IsLimLight_ = false;

	};

}