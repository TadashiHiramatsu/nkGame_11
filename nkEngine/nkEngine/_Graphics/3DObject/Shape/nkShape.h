/**
* �`��̊��N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �`��̊��N���X.
	*/
	class IShape : public IComponent
	{
	public:

		/** 
		* ���_�o�b�t�@�\����. 
		*/
		struct VertexBufferS
		{
			Vector4 Pos;
			Vector3 Normal;
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
		};

	public:

		/**
		* �R���X�g���N�^.
		*/
		IShape(IGameObject* go) : 
			IComponent(go)
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~IShape()
		{
		}

		/**
		* �쐬.
		*
		* @param light		���C�g�̃|�C���^.
		* @param camera		�J�����̃|�C���^.
		*/
		void Create(Light* light, Camera* camera);

		/**
		* �`��.
		*/
		void Render()override;

	protected:

		/**
		* �o�b�t�@�̍쐬.
		*/
		virtual void CreateBuffer();
		 
	protected:

		/** ���_�V�F�[�_. */
		Shader VShader_;
		/** �s�N�Z���V�F�[�_. */
		Shader PShader_;

		/** ���_�o�b�t�@. */
		VertexBuffer VertexBuffer_;
		/** �C���f�b�N�X�o�b�t�@. */
		IndexBuffer IndexBuffer_;
		/** VS�X�e�[�W�̒萔�o�b�t�@. */
		ConstantBuffer VSConstantBuffer_;
		/** PS�X�e�[�W�̒萔�o�b�t�@. */
		ConstantBuffer PSConstantBuffer_;

		/** ���C�g. */
		Light* Light_ = nullptr;
		/** �J����. */
		Camera* Camera_ = nullptr;

	};

}