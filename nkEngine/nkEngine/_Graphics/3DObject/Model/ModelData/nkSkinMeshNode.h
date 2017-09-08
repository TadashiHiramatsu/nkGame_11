/**
* スキンメッシュノードクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* スキンメッシュノードクラス.
	*/
	class SkinMeshNode : public INode
	{
	public:

		/**
		* ボーン.
		*/
		struct BoneS
		{
			BoneS(UINT index,float weight)
			{
				BoneIndex_ = index;
				BoneWeight_ = weight;
			}
			UINT BoneIndex_;
			float BoneWeight_;
		};
		/**
		* ボーン情報.
		*/
		struct VertexBoneS
		{
			vector<BoneS> Bone_;
		};

		/** 最大ボーン数. */
		static const UINT BONE_MAX_SIZE = 4U;

		/**
		* 頂点バッファ.
		*/
		struct VertexBufferS
		{
			Vector4 Pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);	//!< 頂点座標.
			Vector2 Tex = Vector2::Zero;					//!< UV座標.
			Vector3 Normal = Vector3::Zero;					//!< 法線ベクトル.
			Vector3 Tangent = Vector3::Zero;				//!< 接ベクトル
			UINT BoneIndex_[BONE_MAX_SIZE] = { 0 };			//!< ボーン番号.
			float BoneWeight_[BONE_MAX_SIZE] = { 0.0f };	//<! ボーンウェイト.
		};

	public:

		/**
		* コンストラクタ.
		*/
		SkinMeshNode()
		{
		}

		/**
		* デストラクタ.
		*/
		~SkinMeshNode()
		{
		}

		/**
		* 作成.
		*
		* @param fbxNode	FBXSDKのノードクラス.
		* @param parent		親のポインタ.
		* @param modelData	モデルデータ.
		*/
		void Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)override;

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
		void CreateVertexBuffer(FbxMesh* fbxMesh, ModelData* modelData);

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
		void CreateMaterial(FbxNode* fbxNode, ModelData* modelData);

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