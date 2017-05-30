/**
 * �Q�[���I�u�W�F�N�g�N���X�̒�`.
 */
#pragma once

#include"_Component\nkTransform.h"

namespace nkEngine
{

	/** �D��x. */
	typedef unsigned char GOPriorityT;

	/**
	 * �Q�[���I�u�W�F�N�g�}�l�[�W���ɓo�^������N���X.
	 * �Q�[���J���ł͊�{���̃N���X���p��������.
	 */
	class IGameObject : Noncopyable
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
		 * �R���X�g���N�^�̌�ɌĂ΂�鏉����.
		 */
		virtual void Awake() 
		{
		}

		/**
		 * ������.
		 */
		virtual void Start() 
		{
		}

		/**
		 * Update�̑O�ɌĂ΂��X�V.
		 */
		virtual void PreUpdate()
		{
		}

		/**
		 * �X�V.
		 */
		virtual void Update() 
		{
		}

		/**
		 * Update�̌�ɌĂ΂��X�V.
		 */
		virtual void PostUpdate() 
		{
		}

		/**
		 * Render�̑O�ɌĂ΂��`��.
		 */
		virtual void PreRender() 
		{
		}

		/**
		 * �`��.
		 */
		virtual void Render() 
		{
		}

		/**
		 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		 */
		virtual void PostRender() 
		{
		}

		/**
		 * �f�X�g���N�^�̑O�ɌĂ΂����.
		 */
		virtual void Release() 
		{
		}

		/**
		* �f�[�^�̃Z�[�u���s��.
		*/
		virtual void Save()
		{
		}

	public:

		/**
		 * �R���X�g���N�^�̌�ɌĂ΂�鏉����.
		 * ���b�p�[.
		 */
		virtual void AwakeWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Awake();
			}
		}

		/**
		 * ������.
		 * ���b�p�[.
		 */
		virtual void StartWrapper()
		{
			if (!isStart_ && isActive_)
			{
				Start();
				isStart_ = true;
			}
		}

		/**
		 * Update�̑O�ɌĂ΂��X�V.
		 * ���b�p�[.
		 */
		virtual void PreUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreUpdate();
			}
		}

		/**
		 * �X�V.
		 * ���b�p�[.
		 */
		virtual void UpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				Update();
			}
		}

		/**
		 * Update�̌�ɌĂ΂��X�V.
		 * ���b�p�[.
		 */
		virtual void PostUpdateWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostUpdate();
			}
		}

		/**
		 * Render�̑O�ɌĂ΂��`��.
		 * ���b�p�[.
		 */
		virtual void PreRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PreRender();
			}
		}

		/**
		 * �`��.
		 * ���b�p�[.
		 */
		virtual void RenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				Render();
			}
		}

		/**
		 * �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		 * ���b�p�[.
		 */
		virtual void PostRenderWrapper()
		{
			if (isStart_ && isActive_)
			{
				PostRender();
			}
		}

	public:

		/**
		 * �Q�[���I�u�W�F�N�g��isActive���擾.
		 *
		 * @return True if it succeeds, false if it fails.
		 */
		bool GetActive() const
		{
			return isActive_;
		}

		/**
		 * �Q�[���I�u�W�F�N�g���A�N�e�B�u / ��A�N�e�B�u�ɂ��܂�.
		 *
		 * @param value True to value.
		 */
		void SetActive(bool value)
		{
			isActive_ = value;
		}

		/**
		 * �D��x���擾.
		 *
		 * @return The priority.
		 */
		GOPriorityT GetPriority() const
		{
			return Priority_;
		}

	public:

		/** �g�����X�t�H�[���N���X. */
		Transform Transform_;

		/** �D��x. */
		GOPriorityT Priority_ = 0;
		/** �A�N�e�B�u�t���O. */
		bool isActive_ = true;
		/** Start���Ă΂�Ă��邩�t���O. */
		bool isStart_ = false;

	};

}// namespace nkEngine