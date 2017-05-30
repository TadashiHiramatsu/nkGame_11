/**
* ���f���f�[�^�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkModelData.h"

namespace nkEngine
{

	/**
	* �ǂݍ���.
	*
	* @param fileName	�t�@�C����.
	*/
	void ModelData::Load(string fileName, Transform* parent)
	{
		//�������Ǘ��N���X.
		FbxManager* FBXManager = FbxManager::Create();

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

		//DirectX�K�i�ɃR���o�[�g.
		FbxAxisSystem OurAxisSystem(FbxAxisSystem::eMayaYUp);
		OurAxisSystem.ConvertScene(FBXScene);

		//Unity�̒P�ʂɍ��킳�������ȁH
		FbxSystemUnit::m.ConvertScene(FBXScene);

		//���b�V���쐬.
		CreateMesh(FBXScene, parent);

		FBXScene->Destroy();
		FBXManager->Destroy();
	}

	/**
	* �X�V.
	*/
	void ModelData::Update()
	{
		for (auto& it : MeshList_)
		{
			it->Update();
		}
	}

	/**
	* ���b�V���쐬.
	*
	* @param fbxScene	FBXSDK�̃V�[���N���X.
	*/
	void ModelData::CreateMesh(FbxScene * fbxScene,Transform* parent)
	{
		FbxNode* FBXRootNode = fbxScene->GetRootNode();
	
		ProbeNode(FBXRootNode, parent);
	}

	/**
	* �m�[�h�T��.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	* @param parent		�e�̃g�����X�t�H�[���|�C���^.
	*/
	void ModelData::ProbeNode(FbxNode * fbxNode, Transform* parent)
	{
		//�m�[�h�������.
		if (fbxNode)
		{
			//������.
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