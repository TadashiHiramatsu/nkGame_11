/**
* モデルデータクラスの定義.
*/
#pragma once

#include"_Object\Component\nkComponent.h"

#include"ModelData\nkNode.h"
#include"ModelData\nkMaterial.h"
#include"ModelData\nkSkeleton.h"

namespace nkEngine
{

	/**
	* モデルデータクラス.
	*/
	class ModelData : public IComponent
	{
	public:

		/** ノードリスト定義.. */
		using NodeList = vector<INode*>;

	public:

		/**
		* コンストラクタ.
		*/
		ModelData(IGameObject* go) : 
			IComponent(go)
		{
			Name_ = "ModelData";
		}

		/**
		* デストラクタ.
		*/
		~ModelData()
		{
		}

		/**
		* 読み込み.
		*
		* @param fileName	ファイル名.
		*/
		void Load(string fileName);

		/**
		* 更新.
		*/
		void Update()override;

		/**
		* ノードリストの取得.
		*/
		NodeList& GetNodeList()
		{
			return NodeList_;
		}

		/**
		* マテリアルリストの取得.
		*/
		vector<Material*>& GetMaterialList()
		{
			return MaterialList_;
		}

		/**
		* スケルトンクラスを取得.
		*/
		Skeleton* GetSkeleton()
		{
			return Skeleton_;
		}

		/**
		* ノード名からノードを取得.
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
		* ノード探索.
		*
		* @param fbxNode	FBXSDKのノードクラス.
		* @param parent		親のポインタ. 
		*/
		void ProbeNode(FbxNode* fbxNode,Transform* parent);

	private:

		/** ノードリスト. */
		NodeList NodeList_;

		/** マテリアルリスト. */
		vector<Material*> MaterialList_;

		/** スケルトンクラス. */
		Skeleton* Skeleton_ = nullptr;

	};

}