/**
* メッシュクラスの定義.
*/
#pragma once

namespace nkEngine
{

	class ModelData;
	class Material;

	/**
	* メッシュクラス.
	*/
	class Mesh : Noncopyable
	{
	public:

		/**
		* 頂点バッファ構造体.
		*/
		struct VertexBufferS
		{
			Vector4 Pos = Vector4(0, 0, 0, 1);	//!< 頂点.
			Vector2 Tex = Vector2::Zero;		//!< UV座標.
			Vector3 Normal = Vector3::Zero;		//!< 法線ベクトル.
			Vector3 Tangent = Vector3::Zero;	//!< 接ベクトル
		};

	public:

		/**
		* 読み込み.
		*
		* @param fbxMesh	FBXSDKのメッシュクラス.
		* @param parent		親のトランスフォームポインタ.
		*/
		void Load(FbxMesh* fbxMesh,Transform* parent, ModelData* modelData);

		/**
		* 更新.
		*/
		void Update();

		/**
		* 描画.
		*/
		void Render();

		/**
		* ワールド行列を取得.
		*/
		const Matrix& GetWorldMatrix()
		{
			return LocalTransform_.WorldMatrix_;
		}

		/**
		* トランスフォームのポインタを取得.
		*/
		Transform* GetTransform()
		{
			return &LocalTransform_;
		}

		/**
		* 対応したマテリアル番号を取得.
		*/
		int GetMaterialNum() const
		{
			return MaterialNum_;
		}

	private:
		 
		/**
		* バッファの作成.
		*
		* @param fbxMesh	FBXSDKのメッシュクラス.
		*/
		void CreateBuffer(FbxMesh* fbxMesh);

		/**
		* マテリアルの作成.
		*
		* @param fbxNode	FBXSDKのノードクラス. 
		*/
		void CreateMaterial(FbxNode* fbxNode,ModelData* modelData);

	private:

		/** メッシュ名. */
		string Name_ = "NonName";

		/** ローカルトランスフォーム. */
		Transform LocalTransform_;

		/** 頂点バッファ. */
		VertexBuffer VertexBuffer_;
		/** 頂点数. */
		UINT VertexCount_ = 0;

		/** 対応するマテリアル番号. */
		int MaterialNum_ = -1;

		/** UVセット名. */
		string UVSetName_;

	};

}