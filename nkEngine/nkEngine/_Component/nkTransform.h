/**
 * トランスフォームクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * トランスフォームクラス.
	 */
	class Transform : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 */
		Transform()
		{
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
		void Update();

		/**
		 * ビルボードする更新.
		 */
		void BillboardUpdate(const Matrix& rot);
	
	public:

		/** 親のトランスフォーム. */
		Transform* Parent_ = nullptr;

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

}// namespace nkEngine