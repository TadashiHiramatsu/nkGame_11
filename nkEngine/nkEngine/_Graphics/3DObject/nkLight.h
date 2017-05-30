/**
 * ���C�g�N���X�̒�`
 */
#pragma once

namespace nkEngine
{

	/**
	 * ���C�g�N���X.
	 */
	class Light
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		Light();

		/**
		 * �f�X�g���N�^.
		 */
		~Light()
		{
		}

		/**
		 * �f�B�t���[�Y���C�g�̌�����ݒ�.
		 *
		 * @param no	   ���C�g�̔ԍ�.
		 * @param lightDir ���C�g�̕����A���K���ς݃x�N�g��.
		 */
		void SetDiffuseLightDirection(int no, const Vector3& lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "���C�g�̐��吙������");
			DiffuseLightDirection_[no] = Vector4(lightDir.x, lightDir.y, lightDir.z, 1.0f);
		}

		/**
		 * �f�B�t���[�Y���C�g�̌������擾.
		 *
		 * @param no ���C�g�̔ԍ�.
		 *
		 * @return The diffuse light direction.
		 */
		const Vector4& GetDiffuseLightDirection(int no) const
		{
			return DiffuseLightDirection_[no];
		}

		/**
		 * �f�B�t���[�Y���C�g�̐F��ݒ�.
		 *
		 * @param no	   ���C�g�̔ԍ�.
		 * @param lightColor ���C�g�̐F�A0.0f�`1.0f�̒l.
		 */
		void SetDiffuseLightColor(int no, const Vector4& lightColor)
		{
			NK_ASSERT(no < LIGHT_NUM, "���C�g�̐F�吙������");
			DiffuseLightColor_[no] = lightColor;
		}

		/**
		 * �f�B�t���[�Y���C�g�̐F���擾.
		 *
		 * @param no The ���C�g�̔ԍ�.
		 *
		 * @return The diffuse light color.
		 */
		const Vector4& GetDiffuseLightColor(int no) const
		{
			return DiffuseLightColor_[no];
		}

		/**
		 * �A���r�G���g���C�g�̋�����ݒ�.
		 *
		 * @param amb �A���r�G���g�̐F.
		 */
		void SetAmbientLight(const Vector4& amb)
		{
			AmbientLight_ = amb;
		}

		/**
		 * �A���r�G���g���C�g���擾.
		 *
		 * @return The ambient light.
		 */
		const Vector4& GetAmbientLight() const
		{
			return AmbientLight_;
		}

	public:

		/** ���C�g�̐�. */
		static const USHORT LIGHT_NUM = 6;
	
	private:

		/** ���s�����̕���. */
		Vector4 DiffuseLightDirection_[LIGHT_NUM];
		/** ���s�����̐F. */
		Vector4	DiffuseLightColor_[LIGHT_NUM];
		/** ����. */
		Vector4	AmbientLight_;

	};

}