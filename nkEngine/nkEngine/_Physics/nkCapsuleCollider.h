/**
 * �J�v�Z���R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * �J�v�Z���R���C�_�[.
	 */
	class CapsuleCollider : public ICollider
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		CapsuleCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~CapsuleCollider()
		{
		}

		/**
		 * �J�v�Z���R���C�_�[�쐬.
		 *
		 * @param radius	���a.
		 * @param height	����.
		 */
		void Create(const float radius, const float height);

		/**
		* ���.
		*/
		void Release()override
		{
		}

	};

}