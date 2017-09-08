/**
* コンポーネント管理クラスの定義.
*/
#pragma once

#include"nkComponent.h"

namespace nkEngine
{

	/**
	* コンポーネント管理クラス.
	*/
	class ComponentManager : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		ComponentManager(IGameObject* gameObject)
		{
			GameObject_ = gameObject;
		}

		/**
		* デストラクタ.
		*/
		~ComponentManager()
		{
		}

		/**
		* 初期化.
		*/
		void Start();

		/**
		* Updateの前に呼ばれる更新.
		*/
		void PreUpdate();

		/**
		* 更新.
		*/
		void Update();

		/**
		* Updateの後に呼ばれる更新.
		*/
		void PostUpdate();

		/**
		* Renderの前に呼ばれる描画.
		*/
		void PreRender();

		/**
		* 描画.
		*/
		void Render();

		/**
		* ポストエフェクトの後に呼ばれる描画.
		*/
		void PostRender();

		/**
		* コンポーネントを削除.
		*/
		void Remove();

		/**
		* コンポーネントの追加.
		*/
		void AddComponent(IComponent* component)
		{
			//追加.
			ComponentList_.push_back(component);
		}
		/**
		* コンポーネントの追加.
		*/
		template <class TComponent>
		TComponent* AddComponent()
		{
			//作成.
			TComponent* component = new TComponent(GameObject_);
			//初期化.
			component->Awake();
			//追加.
			ComponentList_.push_back(component);
			//返す.
			return component;
		}

		/**
		* コンポーネントを取得.
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
		* コンポーネントを削除.
		*/
		void RemoveComponent(IComponent* component)
		{
			RemoveComponentList_.push_back(component);
		}

	private:

		/** ゲームオブジェクトのポインタ. */
		IGameObject* GameObject_ = nullptr;

		/** コンポーネントリスト. */
		vector<IComponent*> ComponentList_;
		/** 削除するコンポーネント. */
		vector<IComponent*> RemoveComponentList_;

	};

}