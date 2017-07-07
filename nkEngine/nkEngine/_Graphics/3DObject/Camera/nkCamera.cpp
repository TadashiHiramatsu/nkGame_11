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

		if (CalcType_ == CalcTypeCodeE::DirDistance)
		{
			//視線ベクトルを正規化.
			Direction_.Normalize();
			
			switch (CameraType_)
			{
			case CameraTypeCodeE::FirstPerson:
				
				//視点と視線から注視点を計算.
				Target_.Add(Direction_, Position_);
				
				break;
			case CameraTypeCodeE::ThirdPerson:

				//視線に距離を乗算.
				Direction_.Scale(Distance_);
				
				//逆視線から視点を計算.
				Position_.Add(Direction_, Target_);

				break;
			default:
				break;
			}

		}

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
		if (CalcType_ == CalcTypeCodeE::DirDistance)
		{
			Matrix tmp = Matrix::Identity;

			//行列をY軸回りに回転.
			tmp.MakeRotationY(angle);

			//正規化.
			Direction_.Normalize();
			//視線ベクトルに反映.
			Direction_.TransformCoord(tmp);
		}
	}

	/**
	* 縦回転.
	*
	* @param angle 回転量(度).
	*/
	void Camera::SpinVertically(float angle)
	{
		if (CalcType_ == CalcTypeCodeE::DirDistance)
		{
			//クォータニオン.
			Quaternion qua = Quaternion::Identity;
			//回転行列.
			Matrix tmp = Matrix::Identity;

			//正規化.
			Direction_.Normalize();

			//横方向ベクトル.
			Vector3 side = Vector3::Zero;
			side.x = -Direction_.z;
			side.z = Direction_.x;

			//クォータニオンを横軸回りに回転.
			qua.RotationAxis(side, angle);

			//行列をクォータニオンにより回転.
			tmp.MakeRotationQuaternion(qua);

			//視線ベクトルに反映.
			Direction_.TransformCoord(tmp);
		}
	}

}