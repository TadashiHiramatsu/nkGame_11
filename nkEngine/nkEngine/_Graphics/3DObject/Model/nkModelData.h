/**
* モデルデータクラスの定義.
*/
#pragma once

#include"ModelData\nkMesh.h"
#include"ModelData\nkMaterial.h"

namespace nkEngine
{

	/**
	* モデルデータクラス.
	*/
	class ModelData : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		ModelData()
		{
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
		void Load(string fileName, Transform* parent);

		/**
		* 更新.
		*/
		void Update();

		/**
		* メッシュリストの取得.
		*/
		vector<Mesh*>& GetMeshList()
		{
			return MeshList_;
		}

		/**
		* マテリアルリストの取得.
		*/
		vector<Material*>& GetMaterialList()
		{
			return MaterialList_;
		}

	private:

		/**
		* ノード探索.
		*
		* @param fbxNode	FBXSDKのノードクラス.
		* @param parent		親のトランスフォームポインタ. 
		*/
		void ProbeNode(FbxNode* fbxNode,Transform* parent);

	private:

		/** メッシュリスト. */
		vector<Mesh*> MeshList_;
		/** マテリアルリスト. */
		vector<Material*> MaterialList_;

	};

}