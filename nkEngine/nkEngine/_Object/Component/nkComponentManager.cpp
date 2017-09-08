/**
* �R���|�[�l���g�Ǘ��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkComponentManager.h"

namespace nkEngine
{

	/**
	* ������.
	*/
	void ComponentManager::Start()
	{
		for (auto it : ComponentList_)
		{
			it->StartWrapper();
		}
	}

	/**
	* Update�̑O�ɌĂ΂��X�V.
	*/
	void ComponentManager::PreUpdate()
	{
		//�R���|�[�l���g�̍폜.
		Remove();

		for (auto it : ComponentList_)
		{
			it->PreUpdateWrapper();
		}
	}

	/**
	* �X�V.
	*/
	void ComponentManager::Update()
	{
		for (auto it : ComponentList_)
		{
			it->UpdateWrapper();
		}
	}

	/**
	* Update�̌�ɌĂ΂��X�V.
	*/
	void ComponentManager::PostUpdate()
	{
		for (auto it : ComponentList_)
		{
			it->PostUpdateWrapper();
		}
	}

	/**
	* Render�̑O�ɌĂ΂��`��.
	*/
	void ComponentManager::PreRender()
	{
		for (auto it : ComponentList_)
		{
			it->PreRenderWrapper();
		}
	}

	/**
	* �`��.
	*/
	void ComponentManager::Render()
	{
		for (auto it : ComponentList_)
		{
			it->RenderWrapper();
		}
	}

	/**
	* �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
	*/
	void ComponentManager::PostRender()
	{
		for (auto it : ComponentList_)
		{
			it->PostRenderWrapper();
		}
	}

	/**
	* �R���|�[�l���g���폜.
	*/
	void ComponentManager::Remove()
	{
		for (auto com : RemoveComponentList_)
		{
			auto& it = find(ComponentList_.begin(), ComponentList_.end(), com);

			if (it != ComponentList_.end())
			{
				(*it)->OnDestroy();
				delete (*it);
			}

			ComponentList_.erase(it);
		}
		RemoveComponentList_.clear();
	}

}