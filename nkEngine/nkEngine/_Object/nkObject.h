/**
* �I�u�W�F�N�g�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/** ���s�D��x. */
	using PriorityT = unsigned char;

	/**
	* �I�u�W�F�N�g�N���X.
	*/
	class IObject : Noncopyable
	{
	public:
	
		/**
		* �R���X�g���N�^.
		*/
		IObject()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~IObject()
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
		* �j�������Ƃ��ɌĂ΂��.
		*/
		virtual void OnDestroy()
		{
		}

		/**
		* �I�u�W�F�N�g���L��/�A�N�e�B�u�ɂȂ����Ƃ��ɌĂ΂��.
		*/
		virtual void OnEnable()
		{
		}

		/**
		* �I�u�W�F�N�g������/��A�N�e�B�u�ɂȂ����Ƃ��ɌĂ΂��.
		*/
		virtual void OnDisable()
		{
		}

	public:

		/**
		* �R���X�g���N�^�̌�ɌĂ΂�鏉����.
		* ���b�p�[.
		*/
		virtual void AwakeWrapper()
		{
			if (!IsStart_)
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
			if (!IsStart_)
			{
				Start();
				IsStart_ = true;
			}
		}

		/**
		* Update�̑O�ɌĂ΂��X�V.
		* ���b�p�[.
		*/
		virtual void PreUpdateWrapper()
		{
			if (IsStart_ && IsActive_)
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
			if (IsStart_ && IsActive_)
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
			if (IsStart_ && IsActive_)
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
			if (IsStart_ && IsActive_)
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
			if (IsStart_ && IsActive_)
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
			if (IsStart_ && IsActive_)
			{
				PostRender();
			}
		}

	public:

		/**
		* �I�u�W�F�N�g����ݒ�.
		*/
		void SetName(const string& name)
		{
			Name_ = name;
		}

		/**
		* �I�u�W�F�N�g�����擾.
		*/
		const string& GetName() const
		{
			return Name_;
		}

		/**
		* �L���t���O��ݒ肷��.
		*
		* @param active	�t���O.
		*/
		void SetActive(const bool active)
		{
			IsActive_ = active;

			if (active)
			{
				//�L��.
				OnEnable();
			}
			else
			{
				//����.
				OnDisable();
			}
		}

		/**
		* �L���t���O���擾����.
		*/
		bool GetActive() const
		{
			return IsActive_;
		}

		void SetPriority(PriorityT prio)
		{
			Priority_ = prio;
		}

		/**
		* �I�u�W�F�N�g���폜����.
		*
		* @param object	�I�u�W�F�N�g�̃|�C���^.
		*/
		virtual void Destroy(IObject* object) = 0;

	protected:

		/** �I�u�W�F�N�g��. */
		string Name_ = "";

		/** �L���t���O. */
		bool IsActive_ = true;

		/** ���s�D��x. */
		PriorityT Priority_ = 0;

	private:

		/** Start���Ă΂�Ă��邩�t���O. */
		bool IsStart_ = false;

	};

}