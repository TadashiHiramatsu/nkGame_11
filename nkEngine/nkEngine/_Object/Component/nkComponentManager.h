/**
* �R���|�[�l���g�Ǘ��N���X�̒�`.
*/
#pragma once

#include"nkComponent.h"

namespace nkEngine
{

	/**
	* �R���|�[�l���g�Ǘ��N���X.
	*/
	class ComponentManager : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		ComponentManager(IGameObject* gameObject)
		{
			GameObject_ = gameObject;
		}

		/**
		* �f�X�g���N�^.
		*/
		~ComponentManager()
		{
		}

		/**
		* ������.
		*/
		void Start();

		/**
		* Update�̑O�ɌĂ΂��X�V.
		*/
		void PreUpdate();

		/**
		* �X�V.
		*/
		void Update();

		/**
		* Update�̌�ɌĂ΂��X�V.
		*/
		void PostUpdate();

		/**
		* Render�̑O�ɌĂ΂��`��.
		*/
		void PreRender();

		/**
		* �`��.
		*/
		void Render();

		/**
		* �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		*/
		void PostRender();

		/**
		* �R���|�[�l���g���폜.
		*/
		void Remove();

		/**
		* �R���|�[�l���g�̒ǉ�.
		*/
		void AddComponent(IComponent* component)
		{
			//�ǉ�.
			ComponentList_.push_back(component);
		}
		/**
		* �R���|�[�l���g�̒ǉ�.
		*/
		template <class TComponent>
		TComponent* AddComponent()
		{
			//�쐬.
			TComponent* component = new TComponent(GameObject_);
			//������.
			component->Awake();
			//�ǉ�.
			ComponentList_.push_back(component);
			//�Ԃ�.
			return component;
		}

		/**
		* �R���|�[�l���g���擾.
		*/
		IComponent* FindComponent(string name)
		{
			auto& it = find_if(ComponentList_.begin(), ComponentList_.end(), [name](IComponent* co) { return co->GetName() == name; });
			if (it != ComponentList_.end())
			{
				return (*it);
			}
			return nullptr;
		}

		/**
		* �R���|�[�l���g���폜.
		*/
		void RemoveComponent(IComponent* component)
		{
			RemoveComponentList_.push_back(component);
		}

	private:

		/** �Q�[���I�u�W�F�N�g�̃|�C���^. */
		IGameObject* GameObject_ = nullptr;

		/** �R���|�[�l���g���X�g. */
		vector<IComponent*> ComponentList_;
		/** �폜����R���|�[�l���g. */
		vector<IComponent*> RemoveComponentList_;

	};

}