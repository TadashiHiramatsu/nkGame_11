/**
* ���f���f�[�^�N���X�̎���.
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
	* �ǂݍ���.
	*
	* @param fileName	�t�@�C����.
	*/
	void ModelData::Load(string fileName)
	{
		//�������Ǘ��N���X.
		FbxManager* FBXManager = Engine().GetModelManager().GetFBXManager();

		//�ǂݍ��ނ��߂̃N���X.
		FbxImporter* FBXImporter = FbxImporter::Create(FBXManager, "");

		string filePath = "Asset/Model/" + fileName + ".FBX";

		//�ǂݍ���?
		FBXImporter->Initialize(filePath.c_str());

		//�V�[�����.�I�u�W�F�N�g(���b�V��,���C�g,�J����).
		FbxScene* FBXScene = FbxScene::Create(FBXManager, "");

		FBXImporter->Import(FBXScene);

		//�V�[���ɃC���|�[�g�������_�ŕs�v.
		FBXImporter->Destroy();

		//Unity�̒P�ʂɍ��킳�������ȁH
		FbxSystemUnit::m.ConvertScene(FBXScene);

		//DirectX�K�i�ɃR���o�[�g.
		FbxAxisSystem OurAxisSystem(FbxAxisSystem::eMayaYUp);
		OurAxisSystem.ConvertScene(FBXScene, FBXScene->GetRootNode());

		FbxNode* FBXRootNode = FBXScene->GetRootNode();

		ProbeNode(FBXRootNode, &GameObject_->Transform_);

		FBXScene->Destroy();

		IsStart_ = true;
	}

	/**
	* �X�V.
	*/
	void ModelData::Update()
	{
		for (auto& it : NodeList_)
		{
			it->UpdateWrapper();
		}
	}

	/**
	* �m�[�h�T��.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	* @param parent		�e�̃|�C���^.
	*/
	void ModelData::ProbeNode(FbxNode * fbxNode, Transform* parent)
	{
		//�m�[�h�������.
		if (fbxNode)
		{
			//������.
			int attrCount = fbxNode->GetNodeAttributeCount();

			/** �쐬���ꂽ���ǂ����̃m�[�h�|�C���^. */
			INode* node = nullptr;

			//������S�ă��[�v.
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