/**
* �{�[���m�[�h�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkBoneNode.h"

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	* @param parent		�e�̃|�C���^.
	* @param modelData	���f���f�[�^.
	*/
	void BoneNode::Create(FbxNode * fbxNode, Transform * parent, ModelData * modelData)
	{
		//�{�[���^�C�v�ɐݒ�.
		NodeType_ = NodeTypeE::Bone;

		INode::Create(fbxNode, parent, modelData);
	}

}