/**
 * �J�v�Z���R���C�_�[�N���X�̎���.
 */
#include"nkstdafx.h"
#include"nkCapsuleCollider.h"

namespace nkEngine
{

	/**
	* �J�v�Z���R���C�_�[�쐬.
	*
	* @param radius	���a.
	* @param height	����.
	*/
	void CapsuleCollider::Create(const float radius, const float height)
	{
		Shape_ = new btCapsuleShape(radius, height);
	}

}