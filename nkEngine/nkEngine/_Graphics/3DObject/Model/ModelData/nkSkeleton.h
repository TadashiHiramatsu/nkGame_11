/**
* スケルトンクラスの定義.
*/
#pragma once

#include"nkBone.h"

namespace nkEngine
{

	/** ボーンリスト. */
	using BoneList = vector<BonePtr>;

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
		* アニメーションエンドフレームを設定.
		*
		* @param frame	フレーム番号.
		*/
		void SetAnimationEndFrame(UINT frame)
		{
			AnimationEndFrame_ = frame;
		}
		/**
		* アニメーションエンドフレームを取得.
		*/
		UINT GetAnimationEndFrame()
		{
			return AnimationEndFrame_;
		}

		/**
		* 現在のアニメーションフレーム番号を設定.
		*/
		void SetAnimationFrame(UINT frame)
		{
			NowAnimationFrame_ = frame;
		}
		/**
		* 現在のアニメーションフレーム番号を取得.
		*/
		UINT GetAnimationFrame()
		{
			return NowAnimationFrame_;
		}
		
		/**
		* ボーンを取得.
		*
		* @param index	ボーン番号.
		*/
		BonePtr GetBone(UINT index)
		{
			return BoneList_[index];
		}
		/**
		* ボーンを取得.
		*
		* @param name	ボーン名.
		*/
		BonePtr GetBone(string name)
		{
			for (auto& it : BoneList_)
			{
				if (it->GetBoneName() == name)
				{
					return it;
				}
			}
			return nullptr;
		}

		/**
		* ボーンを設定.
		*
		* @param bone	ボーンポインタ.
		*/
		void AddBone(BonePtr bone)
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
			for (auto& it : BoneList_)
			{
				if (it->GetBoneName() == name)
				{
					return it->GetBoneIndex();
				}
			}
			return -1;
		}

	private:

		/**
		* ボーンリスト.
		*/
		BoneList BoneList_;

		/** アニメーションエンドフレーム. */
		UINT AnimationEndFrame_ = 0;
		/** 現在のアニメーションフレーム番号. */
		UINT NowAnimationFrame_ = 0;

	};

}