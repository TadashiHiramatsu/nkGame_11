/**
 * �{�b�N�X�R���C�_�[�N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkBoxCollider.h"

namespace nkEngine
{

	/**
	 * �{�b�N�X�`��̍쐬.
	 *
	 * @param size	�T�C�Y.
	 */
	void BoxCollider::Create(const Vector3& size)
	{
		Shape_ = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
	}

}