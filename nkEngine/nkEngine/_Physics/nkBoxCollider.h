/**
 * �{�b�N�X�R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * �{�b�N�X�R���C�_�[�N���X.
	 */
	class BoxCollider : public ICollider
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		BoxCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~BoxCollider()
		{
		}

		/**
		 * �{�b�N�X�R���C�_�[�쐬.
		 *
		 * @param size	�T�C�Y.
		 */
		void Create(const Vector3& size);

		/**
		* ���.
		*/
		void Release()override
		{
		}

	};

}