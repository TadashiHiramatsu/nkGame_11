/**
 * ���̃R���C�_�[�N���X�̒�`.
 */
#pragma once

#include"nkCollider.h"

namespace nkEngine
{

	/**
	 * ���̃R���C�_�[�N���X.
	 */
	class SphereCollider : public ICollider
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		SphereCollider()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~SphereCollider()
		{
		}

		/**
		 * ���̃R���C�_�[�쐬.
		 *
		 * @param radius	���a.
		 */
		void Create(const float radius);

		/**
		* ���.
		*/
		void Release()override
		{
		}
	
	};

}