/**
 * カプセルコライダークラスの実装.
 */
#include"nkstdafx.h"
#include"nkCapsuleCollider.h"

namespace nkEngine
{

	/**
	* カプセルコライダー作成.
	*
	* @param radius	半径.
	* @param height	高さ.
	*/
	void CapsuleCollider::Create(const float radius, const float height)
	{
		Shape_ = new btCapsuleShape(radius, height);
	}

}