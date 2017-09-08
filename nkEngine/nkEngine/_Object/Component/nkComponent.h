/**
* �R���|�[�l���g�N���X�̒�`. 
*/
#pragma once

#include"..\nkObject.h"

namespace nkEngine
{

	/** �Q�[���I�u�W�F�N�g�N���X. */
	class IGameObject;
	
	/**
	* �R���|�[�l���g�N���X.
	*/
	class IComponent : public IObject
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		IComponent(IGameObject* gameObject)
		{
			//�Q�[���I�u�W�F�N�g��o�^.
			GameObject_ = gameObject;
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~IComponent()
		{
		}

		/**
		* �I�u�W�F�N�g���폜����.
		*
		* @param object	�I�u�W�F�N�g�̃|�C���^.
		*/
		void Destroy(IObject* object);

	public:

		/**
		* ������.
		* ���b�p�[.
		*/
		void StartWrapper()
		{
			if (!IsStart_)
			{
				Start();
				IsStart_ = true;
			}
		}

		/**
		* Update�̑O�ɌĂ΂��X�V.
		* ���b�p�[.
		*/
		void PreUpdateWrapper()
		{
			if (IsStart_ && IsActive_)
			{
				PreUpdate();
			}
		}

		/**
		* �X�V.
		* ���b�p�[.
		*/
		void UpdateWrapper()
		{
			if (IsStart_ && IsActive_)
			{
				Update();
			}
		}

		/**
		* Update�̌�ɌĂ΂��X�V.
		* ���b�p�[.
		*/
		void PostUpdateWrapper()
		{
			if (IsStart_ && IsActive_)
			{
				PostUpdate();
			}
		}

		/**
		* Render�̑O�ɌĂ΂��`��.
		* ���b�p�[.
		*/
		void PreRenderWrapper()
		{
			if (IsStart_ && IsActive_)
			{
				PreRender();
			}
		}

		/**
		* �`��.
		* ���b�p�[.
		*/
		void RenderWrapper()
		{
			if (IsStart_ && IsActive_)
			{
				Render();
			}
		}

		/**
		* �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		* ���b�p�[.
		*/
		void PostRenderWrapper()
		{
			if (IsStart_ && IsActive_)
			{
				PostRender();
			}
		}

	public:

		/** �Q�[���I�u�W�F�N�g�̃|�C���^. */
		IGameObject* GameObject_ = nullptr;

	};

}