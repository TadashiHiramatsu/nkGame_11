/**
* �{�b�N�X�`��N���X�̒�`.
*/
#pragma once

#include"nkShape.h"

namespace nkEngine
{

	/**
	* �{�b�N�X�`��N���X.
	*/
	class BoxShape : public IShape
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		BoxShape(IGameObject* go) : 
			IShape(go)
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~BoxShape()
		{
		}

	private:

		/**
		* �o�b�t�@�̍쐬.
		*/
		void CreateBuffer()override;

	};

}