/**
* �Q�[���I�u�W�F�N�g�N���X�̒�`.
*/
#pragma once

#include"../nkObject.h"

namespace nkEngine
{

	/**
	* �Q�[���I�u�W�F�N�g�}�l�[�W���ɓo�^������N���X.
	* �Q�[���J���ł͊�{���̃N���X���p��������.
	*/
	class IGameObject : public IObject
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		IGameObject()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~IGameObject()
		{
		}

		/**
		* �D��x���擾.
		*/
		PriorityT GetPriority() const
		{
			return Priority_;
		}

		/**
		* �I�u�W�F�N�g���폜����.
		*
		* @param object	�I�u�W�F�N�g�̃|�C���^.
		*/
		void Destroy(IObject* object);

	public:

		/** �g�����X�t�H�[���N���X. */
		Transform Transform_;

	};

}