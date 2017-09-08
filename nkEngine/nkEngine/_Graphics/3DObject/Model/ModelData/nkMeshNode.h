/**
* メッシュノードクラスの定義.
*/
#pragma once

#include"nkNode.h"

namespace nkEngine
{

	class Material;

	/**
	* メッシュノードクラス.
	*/
	class MeshNode : public INode
	{
	public:

		/**
		* 頂点バッファ構造体.
		*/
		struct VertexBufferS
		{
			Vector4 Pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);	//!< 頂点座標.
			Vector2 Tex = Vector2::Zero;		//!< UV座標.
			Vector3 Normal = Vector3::Zero;		//!< 法線ベクトル.
			Vector3 Tangent = Vector3::Zero;	//!< 接ベクトル
		};

	public:

		/**
		* コンストラクタ.
		*/
		MeshNode()
		{
		}

		/**
		* デストラクタ.
		*/
		~MeshNode()
		{
		}

		/**
		* 作成.
		*
		* @param fbxNode	FBXSDKのノードクラス.
		* @param parent		親のポインタ.
		* @param modelData	モデルデータ.
		*/
		void Create(FbxNode* fbxNode,Transform* parent, ModelData* modelData)override;

		/**
		* 描画.
		*/
		void Render()override;

		/**
		* ワールド行列を取得.
		*/
		const Matrix& GetWorldMatrix()
		{
			return Transform_.WorldMatrix_;
		}

		/**
		* 対応したマテリアル番号を取得.
		*/
		int GetMaterialNum() const
		{
			return MaterialNum_;
		}

		/**
		* 頂点座標リストを取得.
		*/
		vector<Vector3>& GetVertexPosList()
		{
			return VertexPosList_;
		}
		
	private:

		/**
		* 頂点バッファの作成.
		*/
		void CreateVertexBuffer(FbxMesh* fbxMesh);

		/**
		* 接ベクトルを作成.
		*
		* @param vertexList	頂点リスト.
		*/
		void CreateTanget(vector<VertexBufferS>& vertexList);

		/**
		* マテリアルの作成.
		*
		* @param fbxNode	FBXSDKのノードクラス. 
		*/
		void CreateMaterial(FbxNode* fbxNode,ModelData* modelData);

	private:

		/** 頂点座標リスト. */
		vector<Vector3> VertexPosList_;
		/** 頂点バッファ. */
		VertexBuffer VertexBuffer_;
		/** 頂点数. */
		UINT VertexCount_ = 0;

		/** 対応するマテリアル番号. */
		int MaterialNum_ = -1;

		/** UVセット名. */
		vector<string> UVSetNameList_;

	};

}