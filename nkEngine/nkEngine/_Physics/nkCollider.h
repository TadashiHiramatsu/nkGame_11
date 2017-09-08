/**
* �R���C�_�[�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	 * �R���C�_�[�̊��N���X.
	 * ���̂̎g�p����R���C�_�[�͂��̃N���X���p�����쐬����.
	 */
	class ICollider : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		ICollider()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~ICollider()
		{
			Release();
		}

		/**
		 * �{�f�B�̎擾.
		 */
		btCollisionShape* GetBody()
		{
			return Shape_;
		}

		/**
		* ���.
		*/
		virtual void Release()
		{
			if (Shape_)
			{
				delete Shape_;
				Shape_ = nullptr;
			}
		}

	protected:

		/** �`��. */
		btCollisionShape* Shape_ = nullptr;

	};

}