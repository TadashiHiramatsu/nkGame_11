/**
 * �Q�[���I�u�W�F�N�g�}�l�[�W���N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{

	/**
	 * �Q�[���I�u�W�F�N�g�}�l�[�W���̏�����.
	 *
	 * @param prioValue The prio value.
	 */
	void GameObjectManagerSingleton::StartGOM(int prioValue)
	{
		//�D��x�̍ō��l��ݒ�
		GOPriorityMax_ = prioValue;

		//���T�C�Y
		GameObjectArray_.resize(GOPriorityMax_);
		DeleteObjectArray_.resize(GOPriorityMax_);
	}

	/**
	 * ������.
	 */
	void GameObjectManagerSingleton::Start()
	{
		for (GameObjectListT objList : GameObjectArray_)
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
		for (GameObjectListT objList : GameObjectArray_) 
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
		for (GameObjectListT objList : GameObjectArray_) 
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
		for (GameObjectListT objList : GameObjectArray_) 
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
		for (GameObjectListT objList : GameObjectArray_) 
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
		for (GameObjectListT objList : GameObjectArray_) 
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
		for (GameObjectListT objList : GameObjectArray_) 
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
		for (GameObjectListT& goList : DeleteObjectArray_) 
		{
			for (IGameObject* go : goList) 
			{

				//�D��x����擾
				GOPriorityT prio = go->GetPriority();
				GameObjectListT& goExecList = GameObjectArray_.at(prio);
				
				//�擾
				auto& it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) 
				{
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
		auto& itList = GameObjectArray_.begin();
		while (itList != GameObjectArray_.end())
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