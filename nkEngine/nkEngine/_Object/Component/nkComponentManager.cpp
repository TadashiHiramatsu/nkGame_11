/**
* コンポーネント管理クラスの実装.
*/
#include"nkstdafx.h"
#include"nkComponentManager.h"

namespace nkEngine
{

	/**
	* 初期化.
	*/
	void ComponentManager::Start()
	{
		for (auto it : ComponentList_)
		{
			it->StartWrapper();
		}
	}

	/**
	* Updateの前に呼ばれる更新.
	*/
	void ComponentManager::PreUpdate()
	{
		//コンポーネントの削除.
		Remove();

		for (auto it : ComponentList_)
		{
			it->PreUpdateWrapper();
		}
	}

	/**
	* 更新.
	*/
	void ComponentManager::Update()
	{
		for (auto it : ComponentList_)
		{
			it->UpdateWrapper();
		}
	}

	/**
	* Updateの後に呼ばれる更新.
	*/
	void ComponentManager::PostUpdate()
	{
		for (auto it : ComponentList_)
		{
			it->PostUpdateWrapper();
		}
	}

	/**
	* Renderの前に呼ばれる描画.
	*/
	void ComponentManager::PreRender()
	{
		for (auto it : ComponentList_)
		{
			it->PreRenderWrapper();
		}
	}

	/**
	* 描画.
	*/
	void ComponentManager::Render()
	{
		for (auto it : ComponentList_)
		{
			it->RenderWrapper();
		}
	}

	/**
	* ポストエフェクトの後に呼ばれる描画.
	*/
	void ComponentManager::PostRender()
	{
		for (auto it : ComponentList_)
		{
			it->PostRenderWrapper();
		}
	}

	/**
	* コンポーネントを削除.
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