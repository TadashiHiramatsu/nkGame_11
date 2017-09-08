/**
 * トランスフォームクラスの定義.
 */
#pragma once

#include"_Object\Component\nkComponent.h"

namespace nkEngine
{

	/**
	 * トランスフォームクラス.
	 */
	class Transform : public IComponent
	{
	public:

		/**
		 * コンストラクタ.
		 */
		Transform(IGameObject* gameObject) : 
			IComponent(gameObject)
		{
			Name_ = "Transform";
		}

		/**
		 * デストラクタ.
		 */
		~Transform()
		{
		}

		/**
		 * ワールド行列などの更新.
		 */
		void Update()override;

		/**
		 * ビルボードする更新.
		 */
		void BillboardUpdate(const Matrix& rot);

		/**
		* 親を設定.
		*/
		void SetParent(Transform* parent)
		{
			//親を設定.
			Parent_ = parent;
			//親に自分を子供として追加.
			parent->AddChildren(this);
		}

		/**
		* 子供を追加.
		*/
		void AddChildren(Transform* child)
		{
			//子供を追加.
			ChildrenList_.push_back(child);
		}

		/**
		* 子供リストを取得.
		*/
		vector<Transform*>& GetChildrenList()
		{
			return ChildrenList_;
		}

	private:

		/** 親のトランスフォーム. */
		Transform* Parent_ = nullptr;
		/** 子のリスト. */
		vector<Transform*> ChildrenList_;

	public:

		/** 位置ベクトル. */
		Vector3 Position_ = Vector3::Zero;
		/** 拡大ベクトル. */
		Vector3 Scale_ = Vector3::One;
		/** 回転ベクトル. */
		Quaternion Rotation_ = Quaternion::Identity;

		/** ローカルのワールド行列. */
		Matrix LocalMatrix_ = Matrix::Identity;
		/** ワールド行列. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** ワールド行列の逆行列. */
		Matrix WorldInvMatrix_ = Matrix::Identity;
		/** 回転行列. */
		Matrix RotationMatrix_ = Matrix::Identity;

	};

}