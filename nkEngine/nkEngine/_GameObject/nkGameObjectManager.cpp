/**
 * ゲームオブジェクトマネージャクラスの実装.
 */
#include"nkstdafx.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{

	/**
	 * ゲームオブジェクトマネージャの初期化.
	 *
	 * @param prioValue The prio value.
	 */
	void GameObjectManagerSingleton::StartGOM(int prioValue)
	{
		//優先度の最高値を設定
		GOPriorityMax_ = prioValue;

		//リサイズ
		GameObjectArray_.resize(GOPriorityMax_);
		DeleteObjectArray_.resize(GOPriorityMax_);
	}

	/**
	 * 初期化.
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
	 * Updateの前に呼ばれる更新.
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
	 * 更新.
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
	 * Updateの後に呼ばれる更新.
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
	 * Renderの前に呼ばれる描画.
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
	 * 描画.
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
	 * ポストエフェクトの後に呼ばれる描画.
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
	 * deleteObjectArrayに登録されているGameObjectを削除する.
	 */
	void GameObjectManagerSingleton::Delete()
	{
		//デリート予定のオブジェクトを全網羅
		for (GameObjectListT& goList : DeleteObjectArray_) 
		{
			for (IGameObject* go : goList) 
			{

				//優先度から取得
				GOPriorityT prio = go->GetPriority();
				GameObjectListT& goExecList = GameObjectArray_.at(prio);
				
				//取得
				auto& it = std::find(goExecList.begin(), goExecList.end(), go);
				if (it != goExecList.end()) 
				{
					//削除
					delete (*it);
				}

				goExecList.erase(it);
			}

			goList.clear();
		}

	}

	/**
	 * 全削除SceneManagerに呼ばれる.
	 * isStaticがtrueの場合消されない.
	 */
	void GameObjectManagerSingleton::AllDelete()
	{
		//イテレータ取得
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