/**
* メッシュクラスの定義.
*/
#pragma once

namespace nkEngine
{

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
			Vector3 Normal = Vector3::Zero;			//!< 法線.
		};

	public:

		/**
		* 読み込み.
		*
		* @param fbxMesh	FBXSDKのメッシュクラス.
		* @param parent		親のトランスフォームポインタ.
		*/
		void Load(FbxMesh* fbxMesh,Transform* parent);

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
		* インデックス数を取得.
		*/
		UINT GetIndexCount()
		{
			return IndexCount_;
		}

		/**
		* トランスフォームのポインタを取得.
		*/
		Transform* GetTransform()
		{
			return &LocalTransform_;
		}

	private:
		 
		/**
		* バッファの作成.
		*
		* @param fbxMesh	FBXSDKのメッシュクラス.
		*/
		void CreateBuffer(FbxMesh* fbxMesh);

	private:

		/** メッシュ名. */
		string Name_ = "NonName";

		/** ローカルトランスフォーム. */
		Transform LocalTransform_;

		/** 頂点バッファ. */
		VertexBuffer VertexBuffer_;
		/** 頂点数. */
		UINT VertexCount_ = 0;
		/** インデックスバッファ. */
		IndexBuffer IndexBuffer_;
		/** インデックス数. */
		UINT IndexCount_ = 0;

	};
}