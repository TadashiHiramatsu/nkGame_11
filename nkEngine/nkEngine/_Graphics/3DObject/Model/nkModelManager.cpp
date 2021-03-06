/**
* モデル管理クラスの実装.
*/
#include"nkstdafx.h"
#include"nkModelManager.h"

namespace nkEngine
{

	/**
	* 初期化.
	*/
	void ModelManager::Init()
	{
		//FbxManagerを初期化.
		FBXManager_ = FbxManager::Create();
	}

	/**
	* 解放.
	*/
	void ModelManager::Release()
	{
		if (FBXManager_ != nullptr)
		{
			FBXManager_->Destroy();
			FBXManager_ = nullptr;
		}
	}

}