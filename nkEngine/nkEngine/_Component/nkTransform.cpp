/**
 * トランスフォームクラスの実装.
 */
#include"nkstdafx.h"
#include"nkTransform.h"

namespace nkEngine
{

	/**
	 * 更新.
	 */
	void Transform::Update()
	{
		Matrix mTrans, mScale;

		//移動行列の計算
		mTrans.MakeTranslation(Position_);
		//回転行列の計算
		RotationMatrix_.MakeRotationQuaternion(Rotation_);
		//拡大行列の計算
		mScale.MakeScaling(Scale_);

		//ローカル行列を計算
		LocalMatrix_.Mul(mScale, RotationMatrix_);
		LocalMatrix_.Mul(LocalMatrix_, mTrans);

		//親子関係を計算
		if (Parent_)
		{
			WorldMatrix_.Mul(LocalMatrix_, Parent_->WorldMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//ワールド行列の逆行列を計算
		WorldInvMatrix_.Inverse(WorldMatrix_);
	
	}

	/**
	* ビルボードする更新.
	*/
	void Transform::BillboardUpdate(const Matrix& rot)
	{
		Matrix mTrans, mScale;

		//移動行列の計算
		mTrans.MakeTranslation(Position_);

		//クォータニオン.
		Quaternion qRot;

		float s;
		s = sin(0);
		qRot.x = rot.m[2][0] * s;
		qRot.y = rot.m[2][1] * s;
		qRot.z = rot.m[2][2] * s;
		qRot.w = cos(0);

		//回転行列.
		Matrix mRot;
		mRot.MakeRotationQuaternion(qRot);

		RotationMatrix_.Mul(rot, mRot);

		//拡大行列の計算
		mScale.MakeScaling(Scale_);

		//ローカル行列を計算
		LocalMatrix_.Mul(mScale, RotationMatrix_);
		LocalMatrix_.Mul(LocalMatrix_, mTrans);

		//親子関係を計算
		if (Parent_)
		{
			WorldMatrix_.Mul(LocalMatrix_, Parent_->WorldMatrix_);
		}
		else
		{
			WorldMatrix_ = LocalMatrix_;
		}

		//ワールド行列の逆行列を計算
		WorldInvMatrix_.Inverse(WorldMatrix_);

	}

}// namespace nkEngine