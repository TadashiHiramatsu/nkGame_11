/**
 * �g�����X�t�H�[���N���X�̒�`.
 */
#pragma once

#include"_Object\Component\nkComponent.h"

namespace nkEngine
{

	/**
	 * �g�����X�t�H�[���N���X.
	 */
	class Transform : public IComponent
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		Transform(IGameObject* gameObject) : 
			IComponent(gameObject)
		{
			Name_ = "Transform";
		}

		/**
		 * �f�X�g���N�^.
		 */
		~Transform()
		{
		}

		/**
		 * ���[���h�s��Ȃǂ̍X�V.
		 */
		void Update()override;

		/**
		 * �r���{�[�h����X�V.
		 */
		void BillboardUpdate(const Matrix& rot);

		/**
		* �e��ݒ�.
		*/
		void SetParent(Transform* parent)
		{
			//�e��ݒ�.
			Parent_ = parent;
			//�e�Ɏ������q���Ƃ��Ēǉ�.
			parent->AddChildren(this);
		}

		/**
		* �q����ǉ�.
		*/
		void AddChildren(Transform* child)
		{
			//�q����ǉ�.
			ChildrenList_.push_back(child);
		}

		/**
		* �q�����X�g���擾.
		*/
		vector<Transform*>& GetChildrenList()
		{
			return ChildrenList_;
		}

	private:

		/** �e�̃g�����X�t�H�[��. */
		Transform* Parent_ = nullptr;
		/** �q�̃��X�g. */
		vector<Transform*> ChildrenList_;

	public:

		/** �ʒu�x�N�g��. */
		Vector3 Position_ = Vector3::Zero;
		/** �g��x�N�g��. */
		Vector3 Scale_ = Vector3::One;
		/** ��]�x�N�g��. */
		Quaternion Rotation_ = Quaternion::Identity;

		/** ���[�J���̃��[���h�s��. */
		Matrix LocalMatrix_ = Matrix::Identity;
		/** ���[���h�s��. */
		Matrix WorldMatrix_ = Matrix::Identity;
		/** ���[���h�s��̋t�s��. */
		Matrix WorldInvMatrix_ = Matrix::Identity;
		/** ��]�s��. */
		Matrix RotationMatrix_ = Matrix::Identity;

	};

}