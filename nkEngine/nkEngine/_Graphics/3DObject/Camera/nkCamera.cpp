/**
* カメラクラスの実装.
*/
#include"nkstdafx.h"
#include"nkCamera.h"

namespace nkEngine
{

	/**
	* 更新.
	*/
	void Camera::Update()
	{
		//アスペクト比の計算
		Aspect_ = (float)Engine().GetFrameW() / (float)Engine().GetFrameH();

		//プロジェクション行列の計算
		ProjMatrix_.MakeProjectionFovLH(Angle_, Aspect_, Near_, Far_);

		//ポジション方向の計算
		PosDirection_.Normalize();

		//ポジションの計算
		PosDirection_.Scale(Distance_);
		Position_.Add(PosDirection_, Target_);

		//ビュー行列の計算
		ViewMatrix_.MakeLookAtLH(Position_, Target_, Up_);

		//ビュー行列の逆行列を計算
		ViewInvMatrix_.Inverse(ViewMatrix_);

		//回転行列を計算
		RotationMatrix_ = ViewInvMatrix_;
		RotationMatrix_.m[3][0] = 0.0f;
		RotationMatrix_.m[3][1] = 0.0f;
		RotationMatrix_.m[3][2] = 0.0f;
		RotationMatrix_.m[3][3] = 1.0f;

		//回転行列の逆行列を計算
		RotationInvMatrix_.Transpose(RotationMatrix_);
	}

	/**
	* 横回転.
	*
	* @param angle 回転量(度).
	*/
	void Camera::SpinHorizontally(float angle)
	{
		Matrix tmp = Matrix::Identity;

		//行列をY軸回りに回転.
		tmp.MakeRotationY(angle);

		PosDirection_.Normalize();

		//ベクトルに反映.
		PosDirection_.TransformCoord(tmp);
	}

	/**
	* 縦回転.
	*
	* @param angle 回転量(度).
	*/
	void Camera::SpinVertically(float angle)
	{
		//クォータニオン.
		Quaternion qua = Quaternion::Identity;
		//回転行列.
		Matrix tmp = Matrix::Identity;

		PosDirection_.Normalize();

		//横方向ベクトル.
		Vector3 side = Vector3::Zero;
		side.x = -PosDirection_.z;
		side.z = PosDirection_.x;

		//クォータニオンを横軸回りに回転.
		qua.RotationAxis(side, angle);

		//行列をクォータニオンにより回転.
		tmp.MakeRotationQuaternion(qua);

		//ベクトルに反映.
		PosDirection_.TransformCoord(tmp);
	}

	/**
	* 任意軸回りの回転.
	*
	* @param vec	任意の軸.
	* @param angle	回転量(度).
	*/
	void Camera::SpinAxis(Vector3 & vec, float angle)
	{
		//クォータニオン.
		Quaternion qua = Quaternion::Identity;
		//回転行列.
		Matrix tmp = Matrix::Identity;

		//クォータニオンを任意軸回りに回転.
		qua.RotationAxis(vec, angle);

		//行列をクォータニオンにより回転.
		tmp.MakeRotationQuaternion(qua);

		//ベクトルに反映.
		PosDirection_.TransformCoord(tmp);
	}

}