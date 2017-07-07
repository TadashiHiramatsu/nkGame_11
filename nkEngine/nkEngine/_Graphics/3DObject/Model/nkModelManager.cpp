/**
* ƒ‚ƒfƒ‹ŠÇ—ƒNƒ‰ƒX‚ÌŽÀ‘•.
*/
#include"nkstdafx.h"
#include"nkModelManager.h"

namespace nkEngine
{

	/**
	* ‰Šú‰».
	*/
	void ModelManager::Init()
	{
		//FbxManager‚ð‰Šú‰».
		FBXManager_ = FbxManager::Create();
	}

	/**
	* ‰ð•ú.
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