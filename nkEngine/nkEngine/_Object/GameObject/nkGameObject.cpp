/**
* �Q�[���I�u�W�F�N�g�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkGameObject.h"

namespace nkEngine
{
	
	/**
	* �I�u�W�F�N�g���폜����.
	*
	* @param object	�I�u�W�F�N�g�̃|�C���^.
	*/
	void IGameObject::Destroy(IObject * object)
	{
		GameObjectManager().DeleteGameObject((IGameObject*)object);
	}

}