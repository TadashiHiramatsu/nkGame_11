/**
 * ベクトルクラスの定義.
 */
#pragma once

namespace nkEngine
{

	class Matrix;

	/**
	 * 二次元ベクトルクラス.
	 */
	class Vector2
	{
	public:

		/**
		 * コンストラクタ.
		 */
		Vector2()
		{
		}

		/**
		 * コンストラクタ.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 */
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		/**
		* 加算.
		*
		* @param v ベクトル.
		*/
		void Add(const Vector2& v)
		{
			x += v.x;
			y += v.y;
		}

		/**
		* 第一引数と第二引数の加算値を代入 +.
		*
		* @param v0 ベクトル.
		* @param v1	ベクトル.
		*/
		void Add(const Vector2& v0, const Vector2& v1)
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
		}

		/**
		* 長さを取得.
		*/
		float Length() const
		{
			return sqrt(LengthSq());
		}
		/**
		* 長さの二乗を取得.
		*/
		float LengthSq() const
		{
			return x * x + y * y;
		}

	public:

		union
		{
			struct { float x, y; };
			float v[2];
		};
	
	public:

		/** ゼロ. */
		static const Vector2 Zero;
		/** ワン. */
		static const Vector2 One;

	};

	/**
	 * 三次元ベクトルクラス.
	 */
	class Vector3
	{
	public:

		/**
		 * コンストラクタ.
		 */
		Vector3()
		{
		}

		/**
		 * コンストラクタ.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 */
		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
		 * 線形補間.
		 *
		 * @details	this = v0 + (v1-v0) * t;
		 *
		 * @param	t 	float.
		 * @param	v0	const Vector3&.
		 * @param	v1	const Vector3&.
		 */
		void Lerp(float t, const Vector3& v0, const Vector3& v1)
		{
			this->x = v0.x + (v1.x - v0.x) * t;
			this->y = v0.y + (v1.y - v0.y) * t;
			this->z = v0.z + (v1.z - v0.z) * t;
		}

		/**
		 * 引数に自身の値をコピーする.
		 *
		 * @details	_dst = this;
		 *
		 * @tparam	TVector	vectorタイプ.
		 * @param [in,out]	dst	Destination for the.
		 */
		template<class TVector>
		void CopyTo(TVector& dst) const
		{
			dst.x = this->x;
			dst.y = this->y;
			dst.z = this->z;
		}

		/**
		 * 要素を設定 =.
		 *
		 * @details	this =.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 * @param	z	The z coordinate.
		 */
		void Set(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		/**
		 * ベクトルの各要素を設定 =.
		 *
		 * @tparam	TVector	Type of the vector.
		 * @param [in,out]	v	The v.
		 */
		template<class TVector>
		void Set(TVector& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		/**
		 * ベクトルの各要素を設定 =.
		 *
		 * @param [in,out]	v	The v to set.
		 */
		/*void Set(btVector3& v)
		{
			this->x = v.x();
			this->y = v.y();
			this->z = v.z();
		}*/

		/**
		* ベクトルを加算 +=.
		*
		* @param v	ベクトル.
		*/
		void Add(const Vector3& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
		}
		/**
		* 第一引数と第二引数の加算値を代入 +.
		*
		* @param v0 ベクトル.
		* @param v1	ベクトル.
		*/
		void Add(const Vector3& v0, const Vector3& v1)
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
			z = v0.z + v1.z;
		}

		/**
		* ベクトルの減算 -=.
		*
		* @param v	ベクトル.
		*/
		void Sub(const Vector3& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		/**
		* 第一引数と第二引数の減算値を代入 -. 
		*
		* @param v0 ベクトル.
		* @param v1	ベクトル.
		*/
		void Sub(const Vector3& v0, const Vector3& v1)
		{
			x = v0.x - v1.x;
			y = v0.y - v1.y;
			z = v0.z - v1.z;
		}

		/**
		* 内積.
		*
		* @param v	ベクトル.
		*/
		float Dot(const Vector3& v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		/**
		* 外積.
		*
		* @param v	ベクトル.
		*/
		void Cross(const Vector3& v)
		{
			float _x = (y * v.z) - (v.y * z);
			float _y = (z * v.x) - (v.z * x);
			float _z = (x * v.y) - (v.x * y);
			x = _x;
			y = _y;
			z = _z;
		}
		/**
		* 第一引数と第二引数の外積値を代入.
		*
		* @param v0 ベクトル.
		* @param v1	ベクトル.
		*/
		void Cross(const Vector3& v0, const Vector3& v1)
		{
			float _x = (v0.y * v1.z) - (v1.y * v0.z);
			float _y = (v0.z * v1.x) - (v1.z * v0.x);
			float _z = (v0.x * v1.y) - (v1.x * v0.y);
			x = _x;
			y = _y;
			z = _z;
		}

		/**
		* 長さを取得.
		*/
		float Length() const
		{
			return sqrt(LengthSq());
		}
		/**
		* 長さの二乗を取得.
		*/
		float LengthSq() const
		{
			return x * x + y * y + z * z;
		}

		/**
		* 拡大 *=.
		*
		* @param s	拡大値.
		*/
		void Scale(float s)
		{
			x *= s;
			y *= s;
			z *= s;
		}

		/**
		* 正規化.
		*/
		void Normalize()
		{
			float len = Length();
			if (len > 0.0f)
			{
				x /= len;
				y /= len;
				z /= len;
			}
			else
			{
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			}
		}

		/**
		* 除算 /=.
		*
		* @param d 除算値.
		*/
		void Div(float d)
		{
			x /= d;
			y /= d;
			z /= d;
		}

		/**
		* 引数の行列によりベクトルをトランスフォームする.
		*
		* @param m0	行列.
		*/
		void TransformCoord(const Matrix& m0)
		{
			DirectX::XMVECTOR& Vec0 = DirectX::XMVectorSet(this->x, this->y, this->z, 1.0f);
			DirectX::XMVECTOR& Vec = DirectX::XMVector3TransformCoord(Vec0, *(DirectX::XMMATRIX*)&m0);
			DirectX::XMFLOAT3 Vec1;
			XMStoreFloat3(&Vec1, Vec);
			Set(Vec1);
		}

	public:

		union
		{
			struct { float x, y, z; };
			float v[3];
		};

	public:

		/** ゼロ. */
		static const Vector3 Zero;
		/** 右. */
		static const Vector3 Right;
		/** 左. */
		static const Vector3 Left;
		/** 上. */
		static const Vector3 Up;
		/** 下. */
		static const Vector3 Down;
		/** 前. */
		static const Vector3 Front;
		/** 後. */
		static const Vector3 Back;
		/** The axis x coordinate. */
		static const Vector3 AxisX;
		/** The axis y coordinate. */
		static const Vector3 AxisY;
		/** The axis z coordinate. */
		static const Vector3 AxisZ;
		/** イチ. */
		static const Vector3 One;

	};

	/**
	* 四次元ベクトルクラス.
	*/
	class Vector4
	{
	public:

		/**
		* コンストラクタ.
		*/
		Vector4()
		{
		}

		/**
		* コンストラクタ.
		*/
		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		/**
		* ベクトルの各要素を代入.
		*
		* @param	x	The x coordinate.
		* @param	y	The y coordinate.
		* @param	z	The z coordinate.
		* @param	w	The w coordinate.
		*/
		void Set(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		/**
		* 引数の三次元ベクトルで代入.
		* wには1.0が設定されます.
		*/
		void Set(const Vector3& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
			w = 1.0f;
		}

		/**
		* 加算.
		*
		* @param v	ベクトル.
		*/
		void Add(const Vector4& v)
		{
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;
		}
		/**
		* 第一引数と第二引数の加算値を代入.
		*
		* @param v0 ベクトル.
		* @param v1	ベクトル.
		*/
		void Add(const Vector4& v0, const Vector4& v1)
		{
			x = v0.x + v1.x;
			y = v0.y + v1.y;
			z = v0.z + v1.z;
			w = v0.w + v1.w;
		}

		/**
		* 減算.
		*
		* @param v	ベクトル.
		*/
		void Sub(const Vector4& v)
		{
			x -= v.x;
			y -= v.y;
			z -= v.z;
		}
		/**
		* 第一引数と第二引数の減算値を代入.
		*
		* @param v0 ベクトル.
		* @param v1	ベクトル.
		*/
		void Sub(const Vector4& v0, const Vector4& v1)
		{
			x = v0.x - v1.x;
			y = v0.y - v1.y;
			z = v0.z - v1.z;
			w = v0.w - v1.w;
		}

		/**
		* 内積.
		*/
		float Dot(const Vector4& v) const
		{
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		/**
		* 長さを取得.
		*/
		float Length() const
		{
			return sqrt(LengthSq());
		}
		/**
		* 長さの二乗を取得.
		*/
		float LengthSq() const
		{
			return x * x + y * y + z * z + w * w;
		}

		/**
		* 拡大.
		*
		* @param s	拡大値.
		*/
		void Scale(float s)
		{
			x *= s;
			y *= s;
			z *= s;
			w *= s;
		}

	public:

		union
		{
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			float v[4];
		};

	public:

		static const Vector4 Zero;

	};

	/**
	* クォータニオンクラス.
	* 四元数.
	*/
	class Quaternion : public Vector4
	{
	public:

		/**
		* コンストラクタ.
		*/
		Quaternion()
		{
		}

		/**
		* コンストラクタ.
		*/
		Quaternion(float x, float y, float z, float w) :
			Vector4(x, y, z, w)
		{
		}

		/**
		* 任意の軸回りの回転.
		*
		* @param axis	任意の軸ベクトル.
		* @param angle	回転値(度).
		*/
		void RotationAxis(const Vector3& axis, float angle)
		{
			float s;
			float halfAngle = DirectX::XMConvertToRadians(angle) * 0.5f;
			s = sin(halfAngle);
			x = axis.x * s;
			y = axis.y * s;
			z = axis.z * s;
			w = cos(halfAngle);
		}

		/**
		* クォータニオン同士の積.
		*
		* @param rot	クォータニオン.
		*/
		void Multiply(const Quaternion& rot)
		{
			float pw, px, py, pz;
			float qw, qx, qy, qz;

			pw = w; px = x; py = y; pz = z;
			qw = rot.w; qx = rot.x; qy = rot.y; qz = rot.z;

			w = pw * qw - px * qx - py * qy - pz * qz;
			x = pw * qx + px * qw + py * qz - pz * qy;
			y = pw * qy - px * qz + py * qw + pz * qx;
			z = pw * qz + px * qy - py * qx + pz * qw;
		}
		/**
		* 第一引数と第二引数のクォータニオンの積を代入.
		* @param rot0	クォータニオン.
		* @param rot1	クォータニオン.
		*/
		void Multiply(const Quaternion& rot0, const Quaternion& rot1)
		{
			float pw, px, py, pz;
			float qw, qx, qy, qz;

			pw = rot0.w; px = rot0.x; py = rot0.y; pz = rot0.z;
			qw = rot1.w; qx = rot1.x; qy = rot1.y; qz = rot1.z;

			w = pw * qw - px * qx - py * qy - pz * qz;
			x = pw * qx + px * qw + py * qz - pz * qy;
			y = pw * qy - px * qz + py * qw + pz * qx;
			z = pw * qz + px * qy - py * qx + pz * qw;
		}

	public:

		/** 素性. */
		static const Quaternion Identity;

	};

}