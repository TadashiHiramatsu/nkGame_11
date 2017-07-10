/**
* ゲームオブジェクト管理クラスの実装.
*/
#include"nkstdafx.h"
#include"nkGameObject.h"
#include"nkGameObjectManager.h"

namespace nkEngine
{

	/**
	* ゲームオブジェクト管理クラスの初期化.
	*
	* @param prioValue The prio value.
	*/
	void GameObjectManagerSingleton::StartGOM(int prioValue)
	{
		//優先度の最高値を設定
		PriorityMax_ = prioValue;

		//リサイズ
		GameObjectList_.resize(PriorityMax_);
	}

	/**
	* 初期化.
	*/
	void GameObjectManagerSingleton::Start()
	{
		for (auto& objList : GameObjectList_)
		{
			for (auto obj : objList)
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
		for (auto& objList : GameObjectList_)
		{
			for (auto obj : objList)
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
		for (auto& objList : GameObjectList_)
		{
			for (auto obj : objList)
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
		for (auto& objList : GameObjectList_)
		{
			for (auto obj : objList)
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
		for (auto& objList : GameObjectList_)
		{
			for (auto obj : objList)
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
		for (auto& objList : GameObjectList_)
		{
			for (auto obj : objList)
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
		for (auto& objList : GameObjectList_)
		{
			for (auto obj : objList)
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
		for (auto go : DeleteObjectList_)
		{
			//優先度から取得
			PriorityT prio = go->GetPriority();
			auto& goExecList = GameObjectList_.at(prio);
				
			//取得
			auto& it = find(goExecList.begin(), goExecList.end(), go);
			if (it != goExecList.end()) 
			{
				//破棄処理.
				(*it)->OnDestroy();
				//削除
				delete (*it);
			}

			goExecList.erase(it);
		}
		DeleteObjectList_.clear();
	}

	/**
	* 全削除SceneManagerに呼ばれる.
	* isStaticがtrueの場合消されない.
	*/
	void GameObjectManagerSingleton::AllDelete()
	{
		//イテレータ取得
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