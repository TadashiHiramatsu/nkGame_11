/**
* モデルデータクラスの実装.
*/
#include"nkstdafx.h"
#include"nkModelData.h"

namespace nkEngine
{

	/**
	* 読み込み.
	*
	* @param fileName	ファイル名.
	*/
	void ModelData::Load(string fileName, Transform* parent)
	{
		//メモリ管理クラス.
		FbxManager* FBXManager = FbxManager::Create();

		//読み込むためのクラス.
		FbxImporter* FBXImporter = FbxImporter::Create(FBXManager, "");

		string filePath = "Asset/Model/" + fileName + ".FBX";

		//読み込み?
		FBXImporter->Initialize(filePath.c_str());

		//シーン情報.オブジェクト(メッシュ,ライト,カメラ).
		FbxScene* FBXScene = FbxScene::Create(FBXManager, "");

		FBXImporter->Import(FBXScene);

		//シーンにインポートした時点で不要.
		FBXImporter->Destroy();

		//DirectX規格にコンバート.
		FbxAxisSystem OurAxisSystem(FbxAxisSystem::eMayaYUp);
		OurAxisSystem.ConvertScene(FBXScene);

		//Unityの単位に合わさったかな？
		FbxSystemUnit::m.ConvertScene(FBXScene);

		//メッシュ作成.
		CreateMesh(FBXScene, parent);

		FBXScene->Destroy();
		FBXManager->Destroy();
	}

	/**
	* 更新.
	*/
	void ModelData::Update()
	{
		for (auto& it : MeshList_)
		{
			it->Update();
		}
	}

	/**
	* メッシュ作成.
	*
	* @param fbxScene	FBXSDKのシーンクラス.
	*/
	void ModelData::CreateMesh(FbxScene * fbxScene,Transform* parent)
	{
		FbxNode* FBXRootNode = fbxScene->GetRootNode();
	
		ProbeNode(FBXRootNode, parent);
	}

	/**
	* ノード探索.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	* @param parent		親のトランスフォームポインタ.
	*/
	void ModelData::ProbeNode(FbxNode * fbxNode, Transform* parent)
	{
		//ノードがあれば.
		if (fbxNode)
		{
			//属性数.
			int attrCount = fbxNode->GetNodeAttributeCount();

			Mesh* mesh = nullptr;

			for (int i = 0; attrCount > i; i++)
			{
				FbxNodeAttribute::EType attrType = fbxNode->GetNodeAttributeByIndex(i)->GetAttributeType();

				if (attrType == FbxNodeAttribute::eMesh)
				{
					mesh = new Mesh();
					mesh->Load(fbxNode->GetMesh(), parent);
				}
			}

			if (mesh != nullptr)
			{
				MeshList_.push_back(mesh);
			}

			for (int i = 0; i < fbxNode->GetChildCount(); i++)
			{
				ProbeNode(fbxNode->GetChild(i), (mesh != nullptr) ? mesh->GetTransform() : parent);
			}

		}
	}

}