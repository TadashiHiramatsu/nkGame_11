/**
* ゲームオブジェクト管理クラスの定義.
*/
#pragma once

namespace nkEngine
{

	/** ゲームオブジェクトクラス. */
	class IGameObject;

	/**
	* ゲームオブジェクト管理クラス.
	* このクラスにゲームオブジェクトを継承したクラスを登録すると 
	* 自動で初期化、更新、描画を呼んでくれる.
	*/
	class GameObjectManagerSingleton : Noncopyable
	{
	private:

		/**
		* コンストラクタ.
		*/
		GameObjectManagerSingleton()
		{
		}

		/**
		* デストラクタ.
		*/
		~GameObjectManagerSingleton()
		{
		}

	public:

		/**
		* インスタンスの取得.
		*
		* @return The instance.
		*/
		static GameObjectManagerSingleton& GetInstance()
		{
			static GameObjectManagerSingleton instance;
			return instance;
		}

		/**
		* ゲームオブジェクトマネージャの初期化.
		*
		* @param prioValue 優先度の最高値.
		*/
		void StartGOM(int prioValue);

	public:

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
		* deleteObjectArrayに登録されているGameObjectを削除する.
		*/
		void Delete();

	public:

		/**
		* GameObject登録.
		*
		* @tparam TGO IGameObjectを継承したクラス.
		* @param prio 優先度.
		*
		* @return Null if it fails, else a pointer to a T.
		*/
		template<class TGO>
		TGO* NewGameObject(PriorityT prio)
		{
			//ゲームオブジェクト作成
			TGO* newGO = new TGO;

			//コンストラクタ、Start間の初期化
			newGO->Awake();

			//優先度設定
			newGO->SetPriority(prio);

			//Listに追加
			GameObjectList_.at(prio).push_back(newGO);

			return newGO;
		}

		/**
		* GameObjectManagerから削除するGameObjectを登録する.
		*
		* @param [in,out] go If none-null, the go.
		*/
		void DeleteGameObject(IGameObject* go)
		{
			//削除Listに追加
			GameObjectList_.at(go->GetPriority()).push_back(go);
		}

		/**
		* 全削除SceneManagerに呼ばれる.
		* isStaticがtrueの場合消されない.
		*/
		void AllDelete();

		/**
		* 全削除.
		* isStaticがtrueの場合でも消す.
		*/
		void Release()
		{
			//イテレータ取得
			auto& itList = GameObjectList_.begin();
			while (itList != GameObjectList_.end())
			{
				itList->clear();
				itList++;
			}
		}
		
	private:

		/** 1優先度に1List. */
		using GameObjectListT = list<IGameObject*>;
		/** 登録されているGameObject. */
		vector<GameObjectListT> GameObjectList_;
		/** 削除するGameObject. */
		vector<GameObjectListT> DeleteObjectList_;
		/** 優先度の最大値を設定. */
		PriorityT PriorityMax_;
		/** 優先度の最大値. */
		static const PriorityT MAX_Priority = 255;

	};

	/**
	* ゲームオブジェクト管理クラスを取得.
	*
	* @return A reference to a GameObjectManagerSingleton.
	*/
	static GameObjectManagerSingleton& GameObjectManager()
	{
		return GameObjectManagerSingleton::GetInstance();
	}

	/**
	* ゲームオブジェクト作成登録.
	*
	* @tparam TGO Type of the tgo.
	* @param prio (Optional) The prio.
	*
	* @return Null if it fails, else a pointer to a TGO.
	*/
	template<class TGO>
	static TGO* NewGO(int prio = 0)
	{
		return GameObjectManager().NewGameObject<TGO>(prio);
	}

	/**
	* ゲームオブジェクト削除登録.
	*
	* @param [in,out] go If non-null, the go.
	*/
	static void DeleteGO(IGameObject* go)
	{
		GameObjectManager().DeleteGameObject(go);
	}

}