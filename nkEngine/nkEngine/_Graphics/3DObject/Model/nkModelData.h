/**
* ���f���f�[�^�N���X�̒�`.
*/
#pragma once

#include"_Object\Component\nkComponent.h"

#include"ModelData\nkNode.h"
#include"ModelData\nkMaterial.h"
#include"ModelData\nkSkeleton.h"

namespace nkEngine
{

	/**
	* ���f���f�[�^�N���X.
	*/
	class ModelData : public IComponent
	{
	public:

		/** �m�[�h���X�g��`.. */
		using NodeList = vector<INode*>;

	public:

		/**
		* �R���X�g���N�^.
		*/
		ModelData(IGameObject* go) : 
			IComponent(go)
		{
			Name_ = "ModelData";
		}

		/**
		* �f�X�g���N�^.
		*/
		~ModelData()
		{
		}

		/**
		* �ǂݍ���.
		*
		* @param fileName	�t�@�C����.
		*/
		void Load(string fileName);

		/**
		* �X�V.
		*/
		void Update()override;

		/**
		* �m�[�h���X�g�̎擾.
		*/
		NodeList& GetNodeList()
		{
			return NodeList_;
		}

		/**
		* �}�e���A�����X�g�̎擾.
		*/
		vector<Material*>& GetMaterialList()
		{
			return MaterialList_;
		}

		/**
		* �X�P���g���N���X���擾.
		*/
		Skeleton* GetSkeleton()
		{
			return Skeleton_;
		}

		/**
		* �m�[�h������m�[�h���擾.
		*/
		INode* FindNode(string name)
		{
			auto node = find_if(NodeList_.begin(), NodeList_.end(), [name](INode* node) {return node->GetName() == name; });
			if (node != NodeList_.end())
			{
				return (*node);
			}
			return nullptr;
		}

	private:

		/**
		* �m�[�h�T��.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X.
		* @param parent		�e�̃|�C���^. 
		*/
		void ProbeNode(FbxNode* fbxNode,Transform* parent);

	private:

		/** �m�[�h���X�g. */
		NodeList NodeList_;

		/** �}�e���A�����X�g. */
		vector<Material*> MaterialList_;

		/** �X�P���g���N���X. */
		Skeleton* Skeleton_ = nullptr;

	};

}