/**
* �s��N���X�̒�`.
*/
#pragma once

#include"nkVector.h"

namespace nkEngine
{

	/**
	* �s��N���X.
	*/
	class Matrix
	{
	public:

		static Matrix& FbxToMatrix(FbxAMatrix& fbxMatrix)
		{
			Matrix matrix;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix.m[i][j] = fbxMatrix.mData[i][j];
				}
			}
			return matrix;
		}

		/**
		* �s��̊e�v�f��ݒ�.
		*/
		template<class TMatrix>
		void Set(TMatrix& matrix)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0;j < 4; j++)
				{
					m[i][j] = matrix.m[i][j];
				}
			}
		}
	
		/**
		* �x�N�g����3x3�s��̐�.
		*
		* @param[out] v �x�N�g��.
		*/
		void Mul3x3(Vector3& v) const
		{
			Vector3 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2];
		}

		/**
		* �O�����x�N�g���ƍs��̐�.
		*
		* @param[out]	v	�x�N�g��.
		*/
		void Mul(Vector3& v) const
		{
			Vector3 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0] + m[3][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1] + m[3][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2] + m[3][2];
		}

		/**
		* �l�����x�N�g���ƍs��̐�.
		*
		* @param[out]	v	�x�N�g��.
		*/
		void Mul(Vector4& v) const
		{
			Vector4 vTmp = v;
			v.x = vTmp.x * m[0][0] + vTmp.y * m[1][0] + vTmp.z * m[2][0] + vTmp.w * m[3][0];
			v.y = vTmp.x * m[0][1] + vTmp.y * m[1][1] + vTmp.z * m[2][1] + vTmp.w * m[3][1];
			v.z = vTmp.x * m[0][2] + vTmp.y * m[1][2] + vTmp.z * m[2][2] + vTmp.w * m[3][2];
			v.w = vTmp.x * m[0][3] + vTmp.y * m[1][3] + vTmp.z * m[2][3] + vTmp.w * m[3][3];
		}

		/**
		* ���s�ړ��s����쐬.
		*
		* @param trans	�x�N�g��.
		*/
		void MakeTranslation(const Vector3& trans)
		{
			*this = Identity;
			m[3][0] = trans.x;
			m[3][1] = trans.y;
			m[3][2] = trans.z;
		}

		/**
		* X�����̉�]�s����쐬.
		*
		* @param angle	��]�p�x(�x).
		*/
		void MakeRotationX(float angle)
		{
			auto& matrix = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angle));
			Set(matrix);
		}

		/**
		* Y�����̉�]�s����쐬.
		*
		* @param angle	��]�p�x(�x).
		*/
		void MakeRotationY(float angle)
		{
			auto& matrix = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angle));
			Set(matrix);
		}

		/**
		* Z�����̉�]�s����쐬.
		*
		* @param angle	��]�p�x(�x).
		*/
		void MakeRotationZ(float angle)
		{
			auto& matrix = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angle));
			Set(matrix);
		}

		/**
		* �N�H�[�^�j�I�������]�s����쐬.
		*
		* @param q	�N�H�[�^�j�I��.
		*/
		void MakeRotationQuaternion(Quaternion& q)
		{
			DirectX::XMVECTOR qua = DirectX::XMVectorSet(q.x, q.y, q.z, q.w);
			auto& matrix = DirectX::XMMatrixRotationQuaternion(qua);
			Set(matrix);
		}

		/**
		* �C�ӂ̎����̉�]�s����쐬.
		*
		* @param axis	�C�ӂ̎�.
		* @param angle	��]��(�x).
		*/
		void MakeRotationAxis(const Vector3& axis, float angle)
		{
			auto& vector = DirectX::XMVectorSet(axis.x, axis.y, axis.z, 1.0f);
			auto& matrix = DirectX::XMMatrixRotationAxis(vector, DirectX::XMConvertToRadians(angle));
			Set(matrix);
		}

		/**
		* �g��s����쐬.
		*
		* @param scale	�g��x�N�g��.
		*/
		void MakeScaling(const Vector3& scale)
		{
			auto& matrix = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
			Set(matrix);
		}

		/**
		* �v���W�F�N�V�����s����쐬.
		*
		* @param angle	��p(���W�A��).
		* @param aspect	�A�X�y�N�g��.
		* @param fNear	�ߕ���.
		* @param fFar	������.
		*/
		void MakeProjectionFovLH(float angle, float aspect, float fNear, float fFar)
		{
			auto& matrix = DirectX::XMMatrixPerspectiveFovLH(angle, aspect, fNear, fFar);
			Set(matrix);
		}

		/**
		* ���s���e�s����쐬.
		*
		* @param w		�r���[�{�����[���̕�.
		* @param h		�r���[�{�����[���̍���.
		* @param fNear	�ߕ���.
		* @param fFar	������.
		*/
		void MakeOrthoProjectionLH(float w, float h, float fNear, float fFar)
		{
			auto& matrix = DirectX::XMMatrixOrthographicLH(w, h, fNear, fFar);
			Set(matrix);
		}

		/**
		* �r���[�s����쐬.
		*
		* @param pos	�J�����̎��_.
		* @param target	�J�����̒����_.
		* @param up		�J�����̏����.
		*/
		void MakeLookAtLH(const Vector3& pos, const Vector3& target, const Vector3& up)
		{
			auto& Pos = DirectX::XMVectorSet(pos.x, pos.y, pos.z, 1.0f);
			auto& Target = DirectX::XMVectorSet(target.x, target.y, target.z, 1.0f);
			auto& Up = DirectX::XMVectorSet(up.x, up.y, up.z, 1.0f);
			auto& matrix = DirectX::XMMatrixLookAtLH(Pos, Target, Up);
			Set(matrix);
		}

		/**
		* �s�񓯎m�̏�Z����.
		*
		* @param m0	�s��.
		* @param m1	�s��.
		*/
		void Mul(const Matrix& m0,const Matrix& m1)
		{
			auto& matrix = DirectX::XMMatrixMultiply(*(DirectX::XMMATRIX*)&m0, *(DirectX::XMMATRIX*)&m1);
			Set(matrix);
		}

		/**
		* �t�s����v�Z.
		*
		* @param m0	���ƂȂ�s��.
		*/
		void Inverse(const Matrix& m0)
		{
			auto& matrix = DirectX::XMMatrixInverse(nullptr, *(DirectX::XMMATRIX*)&m0);
			Set(matrix);
		}

		/**
		* �]�u�s����v�Z.
		*
		* @param m0	���ƂȂ�s��.
		*/
		void Transpose(const Matrix& m0)
		{
			auto& matrix = DirectX::XMMatrixTranspose(*(DirectX::XMMATRIX*)&m0);
			Set(matrix);
		}

	public:

		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};

	public:

		/** �P�ʍs��. */
		static const Matrix Identity;

	};

}