/**
* �m�[�h�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkNode.h"

#include<fbxsdk.h>

namespace nkEngine
{

	/**
	* �쐬.
	*
	* @param fbxNode	FBXSDK�̃m�[�h�N���X.
	* @param parent		�e�̃|�C���^.
	* @param modelData	���f���f�[�^.
	*/
	void INode::Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)
	{
		//���O.
		Name_ = fbxNode->GetName();

		//�e��ݒ�.
		Transform_.SetParent(parent);

		IsStart_ = true;

	}

	/**
	* �X�V.
	*/
	void INode::Update()
	{
		//�g�����X�t�H�[���̍X�V.
		Transform_.Update();
	}

}