/**
* �R���|�[�l���g�N���X�̒�`. 
*/
#pragma once

#include"..\nkObject.h"

namespace nkEngine
{
	
	/**
	* �R���|�[�l���g�N���X.
	*/
	class IComponent : public IObject
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		IComponent()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~IComponent()
		{
		}

	protected:

		/** �g�����X�t�H�[���̃|�C���^. */
		Transform* Transform_ = nullptr;

	};

}