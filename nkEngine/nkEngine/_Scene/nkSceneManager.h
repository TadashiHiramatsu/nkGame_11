/**
 * シーンマネージャクラスの定義.
 */
#pragma once

#include"nkScene.h"

namespace nkEngine
{

	/**
	 * シーンマネージャクラス.
	 * シングルトンクラス.
	 * このクラスにISceneクラスを継承したクラスを登録する.
	 */
	class SceneManagerSingleton : Noncopyable
	{
	private:

		/**
		 * コンストラクタ.
		 */
		SceneManagerSingleton()
		{
		}

		/**
		 * デストラクタ.
		 */
		~SceneManagerSingleton()
		{
		}

	public:

		/**
		 * インスタンスの取得.
		 *
		 * @return	The instance.
		 */
		static SceneManagerSingleton& GetInstance()
		{
			static SceneManagerSingleton instance;
			return instance;
		}

		/**
		 * ISceneクラス継承クラスの初期化を呼び出して 
		 * GameObjectManagerクラスを初期化.
		 *
		 * @tparam	TScene	ISceneクラスを継承したクラス.
		 */
		template <class TScene>
		void ChangeScene()
		{
			if (!NextScene_)
			{
				//シーンに設定
				NextScene_ = new TScene();
			}

			isChange_ = true;
		}

		/**
		* 更新.
		* 次のシーンが登録されていたら変更する.
		*/
		void Update()
		{
			if (isChange_)
			{
				//登録されているゲームオブジェクトを全削除
				GameObjectManager().AllDelete();

				if (NowScene_)
				{
					delete NowScene_;
				}

				NowScene_ = NextScene_;

				//シーンクラスの初期化
				NowScene_->Start();

				delete NextScene_;
				NextScene_ = nullptr;

				isChange_ = false;
			}
		}

	private:

		bool isChange_ = false;

		/** シーンクラス. */
		IScene* NowScene_ = nullptr;
		IScene* NextScene_ = nullptr;

	};

	/**
	 * シーンマネージャーの取得.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to a SceneManagerSingleton.
	 */
	inline SceneManagerSingleton& SceneManager()
	{
		return SceneManagerSingleton::GetInstance();
	}

}