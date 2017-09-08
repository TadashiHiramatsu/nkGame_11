/**
 * 球体コライダークラスの実装.
 */
#include"nkstdafx.h"
#include"nkSphereCollider.h"

namespace nkEngine
{

	/**
	 * 球体コライダーの作成.
	 *
	 * @param	radius	The 半径.
	 */
	void SphereCollider::Create(const float radius)
	{
		Shape_ = new btSphereShape(radius);
	}

}