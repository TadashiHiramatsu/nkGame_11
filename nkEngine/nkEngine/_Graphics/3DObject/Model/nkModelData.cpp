/**
* モデルデータクラスの実装.
*/
#include"nkstdafx.h"
#include"nkModelData.h"

#include<fbxsdk.h>

#include"ModelData\nkNullNode.h"
#include"ModelData\nkBoneNode.h"
#include"ModelData\nkMeshNode.h"
#include"ModelData\nkSkinMeshNode.h"

namespace nkEngine
{

	/**
	* 読み込み.
	*
	* @param fileName	ファイル名.
	*/
	void ModelData::Load(string fileName)
	{
		//メモリ管理クラス.
		FbxManager* FBXManager = Engine().GetModelManager().GetFBXManager();

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

		//Unityの単位に合わさったかな？
		FbxSystemUnit::m.ConvertScene(FBXScene);

		//DirectX規格にコンバート.
		FbxAxisSystem OurAxisSystem(FbxAxisSystem::eMayaYUp);
		OurAxisSystem.ConvertScene(FBXScene, FBXScene->GetRootNode());

		FbxNode* FBXRootNode = FBXScene->GetRootNode();

		ProbeNode(FBXRootNode, &GameObject_->Transform_);

		FBXScene->Destroy();

		IsStart_ = true;
	}

	/**
	* 更新.
	*/
	void ModelData::Update()
	{
		for (auto& it : NodeList_)
		{
			it->UpdateWrapper();
		}
	}

	/**
	* ノード探索.
	*
	* @param fbxNode	FBXSDKのノードクラス.
	* @param parent		親のポインタ.
	*/
	void ModelData::ProbeNode(FbxNode * fbxNode, Transform* parent)
	{
		//ノードがあれば.
		if (fbxNode)
		{
			//属性数.
			int attrCount = fbxNode->GetNodeAttributeCount();

			/** 作成されたかどうかのノードポインタ. */
			INode* node = nullptr;

			//属性を全てループ.
			for (int i = 0; attrCount > i; i++)
			{
				FbxNodeAttribute::EType attrType = fbxNode->GetNodeAttributeByIndex(i)->GetAttributeType();

				switch (attrType)
				{
					case FbxNodeAttribute::EType::eNull:
					{
						node = new NullNode();
						break;
					}
					case FbxNodeAttribute::EType::eSkeleton:
					{
						if (Skeleton_ == nullptr)
						{
							Skeleton_ = new Skeleton();
						}
						node = new BoneNode();
						Skeleton_->AddBone((BoneNode*)node);
						break;
					}
					case FbxNodeAttribute::EType::eMesh:
					{
						bool isSkin = false;
						UINT deformerCount = fbxNode->GetMesh()->GetDeformerCount();
						for (int i = 0; i < deformerCount; i++)
						{
							FbxDeformer* FBXDeformer = fbxNode->GetMesh()->GetDeformer(i);
							if (FBXDeformer->GetDeformerType() == FbxDeformer::eSkin)
							{
								isSkin = true;
							}
						}
						if (isSkin)
						{
							node = new SkinMeshNode();
						}
						else
						{
							node = new MeshNode();
						}
						break;
					}
				}

				if (node != nullptr)
				{
					node->Create(fbxNode, parent, this);
					NodeList_.push_back(node);
					break;
				}
			}

			for (int i = 0; i < fbxNode->GetChildCount(); i++)
			{
				ProbeNode(fbxNode->GetChild(i), (node != nullptr) ? &node->Transform_ : parent);
			}
		}
	}

}