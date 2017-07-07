/**
* ゲームオブジェクトクラスの実装.
*/
#include"nkstdafx.h"
#include"nkGameObject.h"

namespace nkEngine
{
	
	/**
	* オブジェクトを削除する.
	*
	* @param object	オブジェクトのポインタ.
	*/
	void IGameObject::Destroy(IObject * object)
	{
		GameObjectManager().DeleteGameObject((IGameObject*)object);
	}

}