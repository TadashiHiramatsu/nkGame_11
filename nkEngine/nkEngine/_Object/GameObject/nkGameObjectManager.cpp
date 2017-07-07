/**
* �Q�[���I�u�W�F�N�g�Ǘ��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkGameObject.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{

	/**
	* �Q�[���I�u�W�F�N�g�Ǘ��N���X�̏�����.
	*
	* @param prioValue The prio value.
	*/
	void GameObjectManagerSingleton::StartGOM(int prioValue)
	{
		//�D��x�̍ō��l��ݒ�
		PriorityMax_ = prioValue;

		//���T�C�Y
		GameObjectList_.resize(PriorityMax_);
		DeleteObjectList_.resize(PriorityMax_);
	}

	/**
	* ������.
	*/
	void GameObjectManagerSingleton::Start()
	{
		for (GameObjectListT objList : GameObjectList_)
		{
			for (IGameObject* obj : objList)
			{
				obj->StartWrapper();
			}
		}
	}

	/**
	* Update�̑O�ɌĂ΂��X�V.
	*/
	void GameObjectManagerSingleton::PreUpdate()
	{
		for (GameObjectListT objList : GameObjectList_)
		{
			for (IGameObject* obj : objList)
			{
				obj->PreUpdateWrapper();
			}
		}
	}

	/**
	* �X�V.
	*/
	void GameObjectManagerSingleton::Update()
	{
		for (GameObjectListT objList : GameObjectList_)
		{
			for (IGameObject* obj : objList) 
			{
				obj->UpdateWrapper();
			}
		}
	}

	/**
	* Update�̌�ɌĂ΂��X�V.
	*/
	void GameObjectManagerSingleton::PostUpdate()
	{
		for (GameObjectListT objList : GameObjectList_)
		{
			for (IGameObject* obj : objList) 
			{
				obj->PostUpdateWrapper();
			}
		}
	}

	/**
	* Render�̑O�ɌĂ΂��`��.
	*/
	void GameObjectManagerSingleton::PreRender()
	{
		for (GameObjectListT objList : GameObjectList_)
		{
			for (IGameObject* obj : objList) 
			{
				obj->PreRenderWrapper();
			}
		}
	}

	/**
	* �`��.
	*/
	void GameObjectManagerSingleton::Render()
	{
		for (GameObjectListT objList : GameObjectList_)
		{
			for (IGameObject* obj : objList)
			{
				obj->RenderWrapper();
			}
		}
	}

	/**
	* �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
	*/
	void GameObjectManagerSingleton::PostRender()
	{
		for (GameObjectListT objList : GameObjectList_)
		{
			for (IGameObject* obj : objList) 
			{
				obj->PostRenderWrapper();
			}
		}
	}

	/**
	* deleteObjectArray�ɓo�^����Ă���GameObject���폜����.
	*/
	void GameObjectManagerSingleton::Delete()
	{
		//�f���[�g�\��̃I�u�W�F�N�g��S�ԗ�
		for (GameObjectListT& goList : DeleteObjectList_) 
		{
			for (IGameObject* go : goList) 
			{
				//�D��x����擾
				PriorityT prio = go->GetPriority();
				GameObjectListT& goExecList = GameObjectList_.at(prio);
				
				//�擾
				auto& it = find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) 
				{
					(*it)->OnDestroy();
					//�폜
					delete (*it);
				}

				goExecList.erase(it);
			}

			goList.clear();
		}

	}

	/**
	* �S�폜SceneManager�ɌĂ΂��.
	* isStatic��true�̏ꍇ������Ȃ�.
	*/
	void GameObjectManagerSingleton::AllDelete()
	{
		//�C�e���[�^�擾
		auto& itList = GameObjectList_.begin();
		while (itList != GameObjectList_.end())
		{
			auto& it = itList->begin();
			while (it != itList->end())
			{
				delete (*it);
				it = itList->erase(it);
			}

			itList++;
		}
	}

}