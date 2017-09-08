/**
* �Q�[���I�u�W�F�N�g�N���X�̒�`.
*/
#pragma once

#include"../nkObject.h"
#include"../Component/nkComponentManager.h"

namespace nkEngine
{

	/**
	* �Q�[���I�u�W�F�N�g�}�l�[�W���ɓo�^������N���X.
	* �Q�[���J���ł͊�{���̃N���X���p��������.
	*/
	class IGameObject : public IObject
	{
	public:

		/**
		* �R���X�g���N�^.
		*
		* @param name	�I�u�W�F�N�g��.
		*/
		IGameObject() :
			ComponentManager_(this),
			Transform_(this)
		{
			Name_ = "GameObject";
			ComponentManager_.AddComponent(&Transform_);
		}

		/**
		* �R���X�g���N�^.
		*
		* @param name	�I�u�W�F�N�g��.
		*/
		IGameObject(string name) :
			ComponentManager_(this),
			Transform_(this)
		{
			Name_ = name;
			ComponentManager_.AddComponent(&Transform_);
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~IGameObject()
		{
		}

		/**
		* �D��x���擾.
		*/
		PriorityT GetPriority() const
		{
			return Priority_;
		}

		/**
		* �I�u�W�F�N�g���폜����.
		*
		* @param object	�I�u�W�F�N�g�̃|�C���^.
		*/
		void Destroy(IObject* object);

		/**
		* �R���|�[�l���g��ǉ�.
		*/
		void AddComponent(IComponent* component)
		{
			ComponentManager_.AddComponent(component);
		}
		/**
		* �R���|�[�l���g��ǉ�.
		*/
		IComponent* FindComponent(string name)
		{
			return ComponentManager_.FindComponent(name);
		}

		/**
		* �R���|�[�l���g���擾����.
		*/
		template <class TComponent>
		TComponent* AddComponent()
		{
			return ComponentManager_.AddComponent<TComponent>();
		}

		/**
		* �R���|�[�l���g���폜.
		*/
		void RemoveComponent(IComponent* component)
		{
			ComponentManager_.RemoveComponent(component);
		}

		/**
		* �L���t���O��ݒ肷��.
		*
		* @param active	�t���O.
		*/
		void SetActive(const bool active)override
		{
			IsActive_ = active;

			if (active)
			{
				//�L��.
				OnEnable();
			}
			else
			{
				//����.
				OnDisable();
			}

			for (auto it : Transform_.GetChildrenList())
			{
				it->GameObject_->SetActive(IsActive_);
			}
		}

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
				ComponentManager_.Start();
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
				ComponentManager_.PreUpdate();
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
				ComponentManager_.Update();
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
				ComponentManager_.PostUpdate();
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
				ComponentManager_.PreRender();
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
				ComponentManager_.Render();
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
				ComponentManager_.PostRender();
			}
		}

	public:

		/** �g�����X�t�H�[���N���X. */
		Transform Transform_;

	private:

		/** �R���|�[�l���g�Ǘ�. */
		ComponentManager ComponentManager_;

	};

}