/**
 * ���̃R���C�_�[�N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkSphereCollider.h"

namespace nkEngine
{

	/**
	 * ���̃R���C�_�[�̍쐬.
	 *
	 * @param	radius	The ���a.
	 */
	void SphereCollider::Create(const float radius)
	{
		Shape_ = new btSphereShape(radius);
	}

}