/**
* ボーンノードクラスの定義.
*/
#pragma once

#include"nkNode.h"

namespace nkEngine
{

	/**
	* ボーンノードクラス.
	*/
	class BoneNode : public INode
	{
	public:

		/**
		* コンストラクタ.
		*/
		BoneNode()
		{
		}

		/**
		* デストラクタ.
		*/
		~BoneNode()
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
		* ボーン番号を設定.
		*/
		void SetBoneIndex(short index)
		{
			BoneIndex_ = index;
		}
		/**
		* ボーン番号を取得.
		*/
		short GetBoneIndex()
		{
			return BoneIndex_;
		}

		/**
		* 初期姿勢行列を設定.
		*/
		void SetBoneOffsetMatrix(const Matrix& offset)
		{
			BoneOffsetMatrix_ = offset;
		}

	private:

		/** ボーン番号. */
		short BoneIndex_ = -1;

		/** ボーンの初期姿勢行列. */
		Matrix BoneOffsetMatrix_;

	};
}