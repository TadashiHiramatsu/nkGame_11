/**
* コンポーネントクラスの定義. 
*/
#pragma once

#include"..\nkObject.h"

namespace nkEngine
{

	/** ゲームオブジェクトクラス. */
	class IGameObject;
	
	/**
	* コンポーネントクラス.
	*/
	class IComponent : public IObject
	{
	public:

		/**
		* コンストラクタ.
		*/
		IComponent(IGameObject* gameObject)
		{
			//ゲームオブジェクトを登録.
			GameObject_ = gameObject;
		}

		/**
		* デストラクタ.
		*/
		virtual ~IComponent()
		{
		}

		/**
		* オブジェクトを削除する.
		*
		* @param object	オブジェクトのポインタ.
		*/
		void Destroy(IObject* object);

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
			}
		}

	public:

		/** ゲームオブジェクトのポインタ. */
		IGameObject* GameObject_ = nullptr;

	};

}