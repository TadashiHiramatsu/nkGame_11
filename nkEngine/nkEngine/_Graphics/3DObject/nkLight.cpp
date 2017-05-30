/**
 * ���C�g�N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkLight.h"

namespace nkEngine
{

	/**
	 * �R���X�g���N�^.
	 */
	Light::Light()
	{
		//�f�B�t���[�Y���C�g����
		DiffuseLightDirection_[0] = Vector4::Zero;
		DiffuseLightDirection_[1] = Vector4::Zero;
		DiffuseLightDirection_[2] = Vector4::Zero;
		DiffuseLightDirection_[3] = Vector4::Zero;
		DiffuseLightDirection_[4] = Vector4::Zero;
		DiffuseLightDirection_[5] = Vector4::Zero;

		//�f�B�t���[�Y���C�g�F
		DiffuseLightColor_[0] = Color::White;
		DiffuseLightColor_[1] = Color::White;
		DiffuseLightColor_[2] = Color::White;
		DiffuseLightColor_[3] = Color::White;
		DiffuseLightColor_[4] = Color::White;
		DiffuseLightColor_[5] = Color::White;

		//�����̐ݒ�
		AmbientLight_ = Vector4(0.2f, 0.2f, 0.2f,1.0f);
		
	}

}