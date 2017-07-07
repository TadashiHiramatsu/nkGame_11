/**
* オブジェクトクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/** 実行優先度. */
	using PriorityT = unsigned char;

	/**
	* オブジェクトクラス.
	*/
	class IObject : Noncopyable
	{
	public:
	
		/**
		* コンストラクタ.
		*/
		IObject()
		{
		}

		/**
		* デストラクタ.
		*/
		~IObject()
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
		* 破棄されるときに呼ばれる.
		*/
		virtual void OnDestroy()
		{
		}

		/**
		* オブジェクトが有効/アクティブになったときに呼ばれる.
		*/
		virtual void OnEnable()
		{
		}

		/**
		* オブジェクトが無効/非アクティブになったときに呼ばれる.
		*/
		virtual void OnDisable()
		{
		}

	public:

		/**
		* コンストラクタの後に呼ばれる初期化.
		* ラッパー.
		*/
		virtual void AwakeWrapper()
		{
			if (!IsStart_)
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
		virtual void PreUpdateWrapper()
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
		virtual void UpdateWrapper()
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
		virtual void PostUpdateWrapper()
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
		virtual void PreRenderWrapper()
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
		virtual void RenderWrapper()
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
		virtual void PostRenderWrapper()
		{
			if (IsStart_ && IsActive_)
			{
				PostRender();
			}
		}

	public:

		/**
		* オブジェクト名を設定.
		*/
		void SetName(const string& name)
		{
			Name_ = name;
		}

		/**
		* オブジェクト名を取得.
		*/
		const string& GetName() const
		{
			return Name_;
		}

		/**
		* 有効フラグを設定する.
		*
		* @param active	フラグ.
		*/
		void SetActive(const bool active)
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
		}

		/**
		* 有効フラグを取得する.
		*/
		bool GetActive() const
		{
			return IsActive_;
		}

		void SetPriority(PriorityT prio)
		{
			Priority_ = prio;
		}

		/**
		* オブジェクトを削除する.
		*
		* @param object	オブジェクトのポインタ.
		*/
		virtual void Destroy(IObject* object) = 0;

	protected:

		/** オブジェクト名. */
		string Name_ = "";

		/** 有効フラグ. */
		bool IsActive_ = true;

		/** 実行優先度. */
		PriorityT Priority_ = 0;

	private:

		/** Startが呼ばれているかフラグ. */
		bool IsStart_ = false;

	};

}