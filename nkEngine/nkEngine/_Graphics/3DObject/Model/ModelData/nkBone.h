/**
* ボーンクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/** ボーンクラス. */
	class Bone;
	/** ボーンクラスのシェアードポインタ. */
	using BonePtr = shared_ptr<Bone>;

	/** 行列配列. */
	using MatrixList = vector<Matrix>;

	/** インデックス配列. */
	using IndexList = vector<USHORT>;

	/**
	* ボーンクラス.
	*/
	class Bone : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		Bone()
		{
		}

		/**
		* デストラクタ.
		*/
		~Bone()
		{
		}

		/**
		* ボーン名を設定.
		*/
		void SetBoneName(string name)
		{
			BoneName_ = name;
		}
		/**
		* ボーン名を取得.
		*/
		string GetBoneName()
		{
			return BoneName_;
		}

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
		* 親のボーン番号を設定.
		*/
		void SetParentBoneIndex(short index)
		{
			ParentBoneIndex_ = index;
		}
		/**
		* 親のボーン番号を取得.
		*/
		short GetParentBoneIndex()
		{
			return ParentBoneIndex_;
		}

		/**
		* 子供ボーンを追加.
		*
		* @param bone	子供ボーンアドレス.
		*/
		void AddChildBoneIndex(BonePtr bone)
		{
			bone->SetParentBoneIndex(BoneIndex_);
			ChildBoneIndexList_.push_back(bone->GetBoneIndex());
		}
		/**
		* 子供ボーン番号リストを取得.
		*/
		const IndexList& GetChildBoneIndexList()
		{
			return ChildBoneIndexList_;
		}

		/**
		* 1フレームの行列を設定.
		*
		* @param matrix	行列.
		* @param frame	フレーム番号.
		*/
		void SetAnimationMatrix(const Matrix& matrix, USHORT frame)
		{
			AnimationMatrixList_[frame] = matrix;
		}

		/**
		* アニメーション行列リストを取得.
		*/
		const MatrixList& GetAnimationMatrix() const
		{
			return AnimationMatrixList_;
		}

	private:

		/** ボーン名. */
		string BoneName_ = "";
		/** ボーン番号. */
		short BoneIndex_ = -1;

		/** 親のボーン番号リスト. */
		short ParentBoneIndex_ = -1;
		/** 子供のボーン番号リスト. */
		IndexList ChildBoneIndexList_;

		/** 
		* アニメーション時の行列リスト.
		* フレーム単位で登録されている.
		*/
		MatrixList AnimationMatrixList_;

	};
}