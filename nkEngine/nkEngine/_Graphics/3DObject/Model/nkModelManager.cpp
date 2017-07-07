/**
* ���f���Ǘ��N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkModelManager.h"

namespace nkEngine
{

	/**
	* ������.
	*/
	void ModelManager::Init()
	{
		//FbxManager��������.
		FBXManager_ = FbxManager::Create();
	}

	/**
	* ���.
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