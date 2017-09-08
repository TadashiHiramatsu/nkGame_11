/**
 * メッシュコライダークラスの定義.
 */
#pragma once

#include"nkCollider.h"
#include"_Graphics\3DObject\Model\nkModelData.h"

namespace nkEngine
{

	/**
	 * メッシュコライダークラス.
	 */
	class MeshCollider : public ICollider
	{
	private:

		/** 頂点バッファ. */
		using VertexBufferT = std::vector<Vector3>;
		/** インデックスバッファ. */
		using IndexBufferT = std::vector<unsigned int>;

	public:

		/**
		 * コンストラクタ.
		 */
		MeshCollider()
		{
		}

		/**
		 * デストラクタ.
		 */
		~MeshCollider()
		{
		}

		/**
		 * ModelRenderからMeshコライダーを生成.
		 *
		 * @param model			スキンモデル.
		 * @param offsetMatrix	オフセット行列.
		 */
		void Create(ModelData* model, const Matrix* offsetMatrix = nullptr);

		/**
		* 解放.
		*/
		void Release()override
		{
			//頂点バッファ配列の削除
			for (auto& vb : VertexBufferArray_)
			{
				vb.clear();
			}
			VertexBufferArray_.clear();

			//インデックスバッファの削除
			for (auto& ib : IndexBufferArray_)
			{
				ib.clear();
			}
			IndexBufferArray_.clear();

			if (StridingMeshInterface_)
			{
				delete StridingMeshInterface_;
				StridingMeshInterface_ = nullptr;
			}
		}

	private:

		/** 頂点バッファの配列. */
		std::vector<VertexBufferT> VertexBufferArray_;
		/** インデックスバッファの配列. */
		std::vector<IndexBufferT> IndexBufferArray_;

		/** トライアングルインデックスバッファ. */
		btTriangleIndexVertexArray* StridingMeshInterface_ = nullptr;

	};

}