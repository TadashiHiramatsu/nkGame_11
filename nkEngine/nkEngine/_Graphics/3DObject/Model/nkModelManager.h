/**
* モデル管理クラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* モデル管理クラス.
	*/
	class ModelManager : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		ModelManager()
		{
		}

		/**
		* デストラクタ.
		*/
		~ModelManager()
		{
		}

		/**
		* 初期化.
		*/
		void Init();

		/**
		* 解放.
		*/
		void Release();

		/**
		* FBXSDKのメモリ管理クラスを取得.
		*/
		FbxManager* GetFBXManager()
		{
			return FBXManager_;
		}

	private:

		/** FBXSDKのメモリ管理クラス. */
		FbxManager* FBXManager_ = nullptr;

	};


}