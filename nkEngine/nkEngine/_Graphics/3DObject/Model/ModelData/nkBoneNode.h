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

	private:

		/** ボーン番号. */
		short BoneIndex_ = -1;

	};
}