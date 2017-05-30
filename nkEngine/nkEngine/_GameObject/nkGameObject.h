/**
 * ゲームオブジェクトクラスの定義.
 */
#pragma once

#include"_Component\nkTransform.h"

namespace nkEngine
{

	/** 優先度. */
	typedef unsigned char GOPriorityT;

	/**
	 * ゲームオブジェクトマネージャに登録する基底クラス.
	 * ゲーム開発では基本このクラスを継承させる.
	 */
	class IGameObject : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 */
		IGameObject()
		{
		}

		/**
		 * デストラクタ.
		 */
		virtual ~IGameObject()
		{
		}

		/**
		 * コンストラクタの後に呼ばれる初期化.
		 */
		virtual void Awake() 
		{
		}

		/**
		 * 初期化.
		 */
		virtual void Start() 
		{
		}

		/**
		 * Updateの前に呼ばれる更新.
		 */
		virtual void PreUpdate()
		{
		}

		/**
		 * 更新.
		 */
		virtual void Update() 
		{
		}

		/**
		 * Updateの後に呼ばれる更新.
		 */
		virtual void PostUpdate() 
		{
		}

		/**
		 * Renderの前に呼ばれる描画.
		 */
		virtual void PreRender() 
		{
		}

		/**
		 * 描画.
		 */
		virtual void Render() 
		{
		}

		/**
		 * ポストエフェクトの後に呼ばれる描画.
		 */
		virtual void PostRender() 
		{
		}

		/**
		 * デストラクタの前に呼ばれる解放.
		 */
		virtual void Release() 
		{
		}

		/**
		* データのセーブを行う.
		*/
		virtual void Save()
		{
		}

	public:

		/**
		 * コンストラクタの後に呼ばれる初期化.
		 * ラッパー.
		 */
		virtual void AwakeWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Awake();
			}
		}

		/**
		 * 初期化.
		 * ラッパー.
		 */
		virtual void StartWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Start();
				isStart_ = true;
			}
		}

		/**
		 * Updateの前に呼ばれる更新.
		 * ラッパー.
		 */
		virtual void PreUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreUpdate();
			}
		}

		/**
		 * 更新.
		 * ラッパー.
		 */
		virtual void UpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				Update();
			}
		}

		/**
		 * Updateの後に呼ばれる更新.
		 * ラッパー.
		 */
		virtual void PostUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostUpdate();
			}
		}

		/**
		 * Renderの前に呼ばれる描画.
		 * ラッパー.
		 */
		virtual void PreRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreRender();
			}
		}

		/**
		 * 描画.
		 * ラッパー.
		 */
		virtual void RenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				Render();
			}
		}

		/**
		 * ポストエフェクトの後に呼ばれる描画.
		 * ラッパー.
		 */
		virtual void PostRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostRender();
			}
		}

	public:

		/**
		 * ゲームオブジェクトのisActiveを取得.
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool GetActive() const
		{
			return isActive_;
		}

		/**
		 * ゲームオブジェクトをアクティブ / 非アクティブにします.
		 *
		 * @param value True to value.
		 */
		void SetActive(bool value)
		{
			isActive_ = value;
		}

		/**
		 * 優先度を取得.
		 *
		 * @return The priority.
		 */
		GOPriorityT GetPriority() const
		{
			return Priority_;
		}

	public:

		/** トランスフォームクラス. */
		Transform Transform_;

		/** 優先度. */
		GOPriorityT Priority_ = 0;
		/** アクティブフラグ. */
		bool isActive_ = true;
		/** Startが呼ばれているかフラグ. */
		bool isStart_ = false;

	};

}// namespace nkEngine