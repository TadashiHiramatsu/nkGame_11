/**
 * ボックスコライダークラスの実装.
 */
#include"nkstdafx.h"
#include"nkBoxCollider.h"

namespace nkEngine
{

	/**
	 * ボックス形状の作成.
	 *
	 * @param size	サイズ.
	 */
	void BoxCollider::Create(const Vector3& size)
	{
		Shape_ = new btBoxShape(btVector3(size.x * 0.5f, size.y * 0.5f, size.z * 0.5f));
	}

}