/**
* ���f���`��N���X�̒�`.
*/
#pragma once

#include"nkModelData.h"

namespace nkEngine
{

	/**
	* ���f���`��N���X.
	*/
	class ModelRender : Noncopyable
	{
	public:

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
			Vector4 EffectFlag_ = Vector4::Zero;	//!< x:�@���}�b�v, y:�X�y�L�����}�b�v.
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		ModelRender()
		{
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
		void Init(
			string fileName,
			Transform* parent,
			Light* light,
			Camera* camera
		);

		/**
		* �X�V.
		*/
		void Update();

		/**
		* Render�O�̕`��.
		*/
		void PreRender();

		/**
		* �`��.
		*/
		void Render();

		/**
		* �V���h�E�}�b�v�`��.
		*/
		void RenderToShadowMap();

		/**
		* ���f���f�[�^���擾.
		*/
		ModelData& GetModelData()
		{
			return ModelData_;
		}

	private:

		/** ���f���f�[�^. */
		ModelData ModelData_;

		/** �g�����X�t�H�[��. */
		Transform* Transform_ = nullptr;

		/** ���_�V�F�[�_. */
		Shader VShader_;
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

	};

}