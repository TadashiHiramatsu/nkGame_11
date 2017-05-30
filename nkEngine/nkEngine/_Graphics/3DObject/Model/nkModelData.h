/**
* モデルデータクラスの定義.
*/
#pragma once

#include"ModelData\nkMesh.h"

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

	private:
		 
		/**
		* メッシュ作成.
		*
		* @param fbxScene	FBXSDKのシーンクラス.
		*/
		void CreateMesh(FbxScene* fbxScene, Transform* parent);

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

	};

}