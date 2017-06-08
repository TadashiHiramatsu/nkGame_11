/**
* �V���h�E�}�b�v�N���X�̒�`.
*/
#pragma once

#include"../nkBlur.h"

namespace nkEngine
{

	/** ���f���`��N���X. */
	class ModelRender;

	/**
	* �V���h�E�}�b�v�N���X.
	*/
	class ShadowMap : Noncopyable
	{
	public:

		/**
		* �V���h�E���V�[�o�[�p�p�����[�^.
		*/
		struct ShadowReceiverParamS
		{
			/** ���C�g�r���[�s��. */
			Matrix LVMatrix_ = Matrix::Identity;
			/** ���C�g�v���W�F�N�V�����s��. */
			Matrix LPMatrix_ = Matrix::Identity;
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		ShadowMap()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~ShadowMap()
		{
		}

		/**
		* �쐬.
		*/
		void Create();

		/**
		* �X�V.
		*/
		void Update();

		/**
		* �`��.
		*/
		void Render();

		/**
		* ���.
		*/
		void Release();

		/**
		* �L���X�^�[�����X�g�ɒǉ�.
		*
		* @param model	���f���`��N���X.
		*/
		void Entry(ModelRender* model)
		{
			CasterModelList_.push_back(model);
		}

		/**
		* �V���h�E�}�b�v�p�e�N�X�`����SRV���擾.
		*/
		ShaderResourceView& GetShadowMapSRV()
		{
			return Blur_.GetBlurSRV();
			return ShadowMapRT_.GetRenderTargetSRV();
		}

		/**
		* �ߕ��ʂ�ݒ�.
		*
		* @param n	�j�A.
		*/
		void SetNear(float n)
		{
			Near_ = n;
		}

		/**
		* �����ʂ�ݒ�.
		*
		* @param f	�t�@�[.
		*/
		void SetFar(float f)
		{
			Far_ = f;
		}

		/**
		* ���C�g�̎��_��ݒ�.
		*
		* @param pos The position.
		*/
		void SetLightPosition(const Vector3& pos)
		{
			LightPosition_ = pos;
		}

		/**
		* ���C�g�̒����_��ݒ�.
		*
		* @param target The target.
		*/
		void SetLightTarget(const Vector3& target)
		{
			LightTarget_ = target;
		}

		/**
		* ���_�V�F�[�_���擾.
		*/
		Shader& GetVShader()
		{
			return VShader_;
		}

		/**
		* �s�N�Z���V�F�[�_���擾.
		*/
		Shader& GetPShader()
		{
			return PShader_;
		}

		/**
		* ���C�g�r���[�s����擾.
		*/
		const Matrix& GetLVMatrix() const 
		{
			return LVMatrix_;
		}

		/**
		* ���C�g�v���W�F�N�V�����s����擾.
		*/
		const Matrix& GetLPMatrix() const
		{
			return LPMatrix_;
		}

	private:

		/** �L���t���O. */
		bool isEnable_ = true;

		/** �V���h�E�}�b�v�p�����_�����O�^�[�Q�b�g. */
		RenderTarget ShadowMapRT_;
		/** VSM�p�u���[. */
		Blur Blur_;
		/** �e���������ރ��f�����X�g. */
		vector<ModelRender*> CasterModelList_;
		
		/** ���C�g�r���[�s��. */
		Matrix LVMatrix_ = Matrix::Identity;
		/** ���C�g�v���W�F�N�V�����s��. */
		Matrix LPMatrix_ = Matrix::Identity;


		/** ���C�g�̎��_. */
		Vector3 LightPosition_ = Vector3::Up;
		/** ���C�g�̒����_. */
		Vector3 LightTarget_ = Vector3::Zero;

		/** �ߕ���. */
		float Near_ = 1.0f;
		/** ������. */
		float Far_ = 100.0f;
		/** �A�X�y�N�g��. */
		float Aspect_ = 1.0f;
		/** �e�𗎂Ƃ��͈͂̕�. */
		Vector2 ShadowArea_ = Vector2::Zero;

		/** ���_�V�F�[�_. */
		Shader VShader_;
		/** �s�N�Z���V�F�[�_. */
		Shader PShader_;

	};

}