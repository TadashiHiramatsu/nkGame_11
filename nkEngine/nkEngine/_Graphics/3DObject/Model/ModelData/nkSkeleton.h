/**
* スケルトンクラスの定義.
*/
#pragma once

#include"nkBoneNode.h"

namespace nkEngine
{

	/**
	* スケルトンクラス.
	* 骨格を表す.
	*/
	class Skeleton : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		Skeleton()
		{
		}

		/**
		* デストラクタ.
		*/
		~Skeleton()
		{
		}

		/**
		* ボーンを取得.
		*
		* @param index	ボーン番号.
		*/
		BoneNode* GetBone(UINT index)
		{
			return BoneList_[index];
		}
		/**
		* ボーンを取得.
		*
		* @param name	ボーン名.
		*/
		BoneNode* FindBone(string name)
		{
			auto node = find_if(BoneList_.begin(), BoneList_.end(), [name](BoneNode* bone) {return bone->GetName() == name; });
			if (node != BoneList_.end())
			{
				return (*node);
			}
			return nullptr;
		}

		/**
		* ボーンを設定.
		*
		* @param bone	ボーンポインタ.
		*/
		void AddBone(BoneNode* bone)
		{
			//ボーン番号を設定.
			bone->SetBoneIndex(BoneList_.size());
			//リストに登録.
			BoneList_.push_back(bone);
		}

		/**
		* ボーン番号を取得.
		* 存在していればボーン番号.
		* 存在してなければ-1を返す.
		*
		* @param name	ボーン名.
		*/
		int FindBoneIndex(string name)
		{
			auto node = find_if(BoneList_.begin(), BoneList_.end(), [name](BoneNode* bone) {return bone->GetName() == name; });
			if (node != BoneList_.end())
			{
				return (*node)->GetBoneIndex();
			}
			return -1;
		}

	private:

		/**
		* ボーンリスト.
		*/
		vector<BoneNode*> BoneList_;

	};

}