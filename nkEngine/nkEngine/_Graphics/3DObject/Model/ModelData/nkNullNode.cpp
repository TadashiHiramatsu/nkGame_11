/**
* �k���m�[�h�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkNullNode.h"

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	* @param parent		�e�̃|�C���^.
	* @param modelData	���f���f�[�^.
	*/
	void NullNode::Create(FbxNode * fbxNode, Transform * parent, ModelData * modelData)
	{
		//�k���^�C�v�ɐݒ�.
		NodeType_ = NodeTypeE::Null;

		INode::Create(fbxNode, parent, modelData);
	}

}