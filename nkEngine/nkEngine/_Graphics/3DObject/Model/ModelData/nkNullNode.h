/**
* �k���m�[�h�N���X�̒�`.
*/
#pragma once

#include"nkNode.h"

namespace nkEngine
{

	/**
	* �k���m�[�h�N���X.
	*/
	class NullNode : public INode
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		NullNode()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~NullNode()
		{
		}

		/**
		* �쐬.
		*
		* @param fbxNode	FBXSDK�̃m�[�h�N���X.
		* @param parent		�e�̃|�C���^.
		* @param modelData	���f���f�[�^.
		*/
		void Create(FbxNode* fbxNode, Transform* parent, ModelData* modelData)override;

	private:

	};

}