/**
* ゲームオブジェクトクラスの定義.
*/
#pragma once

#include"../nkObject.h"
#include"../Component/nkComponentManager.h"

namespace nkEngine
{

	/**
	* ゲームオブジェクトマネージャに登録する基底クラス.
	* ゲーム開発では基本このクラスを継承させる.
	*/
	class IGameObject : public IObject
	{
	public:

		/**
		* コンストラクタ.
		*
		* @param name	オブジェクト名.
		*/
		IGameObject() :
			ComponentManager_(this),
			Transform_(this)
		{
			Name_ = "GameObject";
			ComponentManager_.AddComponent(&Transform_);
		}

		/**
		* コンストラクタ.
		*
		* @param name	オブジェクト名.
		*/
		IGameObject(string name) :
			ComponentManager_(this),
			Transform_(this)
		{
			Name_ = name;
			ComponentManager_.AddComponent(&Transform_);
		}

		/**
		* デストラクタ.
		*/
		virtual ~IGameObject()
		{
		}

		/**
		* 優先度を取得.
		*/
		PriorityT GetPriority() const
		{
			return Priority_;
		}

		/**
		* オブジェクトを削除する.
		*
		* @param object	オブジェクトのポインタ.
		*/
		void Destroy(IObject* object);

		/**
		* コンポーネントを追加.
		*/
		void AddComponent(IComponent* component)
		{
			ComponentManager_.AddComponent(component);
		}
		/**
		* コンポーネントを追加.
		*/
		IComponent* FindComponent(string name)
		{
			return ComponentManager_.FindComponent(name);
		}

		/**
		* コンポーネントを取得する.
		*/
		template <class TComponent>
		TComponent* AddComponent()
		{
			return ComponentManager_.AddComponent<TComponent>();
		}

		/**
		* コンポーネントを削除.
		*/
		void RemoveComponent(IComponent* component)
		{
			ComponentManager_.RemoveComponent(component);
		}

		/**
		* 有効フラグを設定する.
		*
		* @param active	フラグ.
		*/
		void SetActive(const bool active)override
		{
			IsActive_ = active;

			if (active)
			{
				//有効.
				OnEnable();
			}
			else
			{
				//無効.
				OnDisable();
			}

			for (auto it : Transform_.GetChildrenList())
			{
				it->GameObject_->SetActive(IsActive_);
			}
		}

	public:

		/**
		* 初期化.
		* ラッパー.
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
		* Updateの前に呼ばれる更新.
		* ラッパー.
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
		* 更新.
		* ラッパー.
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
		* Updateの後に呼ばれる更新.
		* ラッパー.
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
		* Renderの前に呼ばれる描画.
		* ラッパー.
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
		* 描画.
		* ラッパー.
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
		* ポストエフェクトの後に呼ばれる描画.
		* ラッパー.
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

		/** トランスフォームクラス. */
		Transform Transform_;

	private:

		/** コンポーネント管理. */
		ComponentManager ComponentManager_;

	};

}