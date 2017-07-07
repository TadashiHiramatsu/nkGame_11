/**
* カメラクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* カメラクラス.
	*/
	class Camera : Noncopyable
	{
	public:

		/**
		* カメラタイプのコード.
		*/
		enum class CameraTypeCodeE
		{
			FirstPerson = 0,	//!< 1人称カメラ.
			ThirdPerson,		//!< 3人称カメラ.
		};

		/**
		* 計算タイプのコード.
		*/
		enum class CalcTypeCodeE
		{
			PosTarget,		//!< 視点と注視点.
			DirDistance,	//!< 視点(注視点)から注視点(視点)方向ベクトルと距離.
		};

	public:

		/**
		* コンストラクタ.
		*/
		Camera()
		{
		}

		/**
		* デストラクタ.
		*/
		~Camera()
		{
		}

		/**
		* 更新.
		*/
		void Update();

		/**
		* 横回転.
		*
		* @param angle 回転量(度).
		*/
		void SpinHorizontally(float angle);

		/**
		* 縦回転.
		*
		* @param angle 回転量(度).
		*/
		void SpinVertically(float angle);

		/**
		* ビュー行列の取得.
		*
		* @return The view matrix.
		*/
		const Matrix& GetViewMatrix() const
		{
			return ViewMatrix_;
		}

		/**
		* ビュー行列の逆行列の取得.
		*
		* @return The view inverse matrix.
		*/
		const Matrix& GetViewInvMatrix() const
		{
			return ViewInvMatrix_;
		}

		/**
		* プロジェクション行列の取得.
		*
		* @return The projection matrix.
		*/
		const Matrix& GetProjectionMatrix() const
		{
			return ProjMatrix_;
		}

		/**
		* 回転行列の取得.
		*
		* @return The rotation matrix.
		*/
		const Matrix& GetRotationMatrix() const
		{
			return RotationMatrix_;
		}

		/**
		* 回転行列の逆行列取得.
		*
		* @return The rotation inverse matrix.
		*/
		const Matrix& GetRotationInvMatrix() const
		{
			return RotationInvMatrix_;
		}

		/**
		* カメラの視点の取得.
		*
		* @return The position.
		*/
		const Vector3& GetPosition() const
		{
			return Position_;
		}

		/**
		* カメラの視点の設定.
		*
		* @param pos 視点ベクトル.
		*/
		void SetPosition(const Vector3& pos)
		{
			Position_ = pos;
		}

		/**
		* カメラの視線ベクトルの取得.
		*
		* @return The position direction.
		*/
		const Vector3& GetDirection() const
		{
			return Direction_;
		}

		/**
		* カメラの視線ベクトルの設定.
		*
		* @param dir 視線ベクトル.
		*/
		void SetDirection(const Vector3& dir)
		{
			Direction_ = dir;
		}

		/**
		* カメラの注視点の取得.
		*
		* @return The target.
		*/
		const Vector3& GetTarget() const
		{
			return Target_;
		}

		/**
		* カメラの注視点の設定.
		*
		* @param target 注視点ベクトル.
		*/
		void SetTarget(const Vector3& target)
		{
			Target_ = target;
		}

		/**
		* カメラの上方向の取得.
		*
		* @return The up.
		*/
		const Vector3& GetUp() const
		{
			return Up_;
		}

		/**
		* カメラの上方向の設定.
		*
		* @param up 上方向ベクトル.
		*/
		void SetUp(const Vector3& up)
		{
			Up_ = up;
		}

		/**
		* カメラの視点、注視点間の距離を取得.
		*
		* @return The distance.
		*/
		const float GetDistance() const
		{
			return Distance_;
		}

		/**
		* カメラの視点、注視点間の距離を設定.
		*
		* @param distance 距離.
		*/
		void SetDistance(float distance)
		{
			Distance_ = distance;
		}

		/**
		* カメラの画角を取得.
		*
		* @return The Angle_.
		*/
		float GetAngle() const
		{
			return Angle_;
		}

		/**
		* カメラの画角を設定.
		*
		* @param angle 画角.
		*/
		void SetAngle(float angle)
		{
			Angle_ = angle;
		}

		/**
		* カメラのアスペクト比を取得.
		*
		* @return The aspect.
		*/
		float GetAspect() const
		{
			return Aspect_;
		}

		/**
		* カメラのアスペクト比を設定.
		*
		* @param aspect アスペクト比.
		*/
		void SetAspect(float aspect)
		{
			Aspect_ = aspect;
		}

		/**
		* カメラのニアを取得.
		*
		* @return The near.
		*/
		float GetNear() const
		{
			return Near_;
		}

		/**
		* カメラのニアを設定.
		*
		* @param fnear ニア.
		*/
		void SetNear(float fnear)
		{
			Near_ = fnear;
		}

		/**
		* カメラのファーを取得.
		*
		* @return The far.
		*/
		float GetFar() const
		{
			return Far_;
		}

		/**
		* カメラのファーを設定.
		*
		* @param ffar ファー.
		*/
		void SetFar(float ffar)
		{
			Far_ = ffar;
		}

		/**
		* カメラタイプを設定.
		*/
		void SetCameraType(CameraTypeCodeE type)
		{
			CameraType_ = type;
		}

		/**
		* 計算タイプを設定.
		*/
		void SetCalcType(CalcTypeCodeE type)
		{
			CalcType_ = type;
		}

	private:

		/** カメラタイプ. */
		CameraTypeCodeE CameraType_ = CameraTypeCodeE::ThirdPerson;
		/** 計算タイプ. */
		CalcTypeCodeE CalcType_ = CalcTypeCodeE::DirDistance;

		/** ビュー行列. */
		Matrix ViewMatrix_ = Matrix::Identity;
		/** ビュー行列の逆行列. */
		Matrix ViewInvMatrix_ = Matrix::Identity;
		/** プロジェクション行列. */
		Matrix ProjMatrix_ = Matrix::Identity;
		/** 回転行列. */
		Matrix RotationMatrix_ = Matrix::Identity;
		/** 回転行列の逆行列. */
		Matrix RotationInvMatrix_ = Matrix::Identity;

		/** カメラの視点. */
		Vector3 Position_ = Vector3::Zero;
		/** カメラの注視点. */
		Vector3 Target_ = Vector3::Zero;
		/** カメラの上方向. */
		Vector3 Up_ = Vector3::Up;

		/** 視線ベクトル. */
		Vector3 Direction_ = Vector3::Zero;
		/** 距離. */
		float Distance_ = 1.0f;

		/** 画角. */
		float Angle_ = DirectX::XMConvertToRadians(45.0f);
		/** アスペクト比. */
		float Aspect_ = 1.0f;
		/** ニア. */
		float Near_ = 0.01f;
		/** ファー. */
		float Far_ = 100.0f;

	};

}