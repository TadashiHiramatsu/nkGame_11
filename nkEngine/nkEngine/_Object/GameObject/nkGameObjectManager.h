/**
* �Q�[���I�u�W�F�N�g�Ǘ��N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/** �Q�[���I�u�W�F�N�g�N���X. */
	class IGameObject;

	/**
	* �Q�[���I�u�W�F�N�g�Ǘ��N���X.
	* ���̃N���X�ɃQ�[���I�u�W�F�N�g���p�������N���X��o�^����� 
	* �����ŏ������A�X�V�A�`����Ă�ł����.
	*/
	class GameObjectManagerSingleton : Noncopyable
	{
	private:

		/**
		* �R���X�g���N�^.
		*/
		GameObjectManagerSingleton()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~GameObjectManagerSingleton()
		{
		}

	public:

		/**
		* �C���X�^���X�̎擾.
		*
		* @return The instance.
		*/
		static GameObjectManagerSingleton& GetInstance()
		{
			static GameObjectManagerSingleton instance;
			return instance;
		}

		/**
		* �Q�[���I�u�W�F�N�g�}�l�[�W���̏�����.
		*
		* @param prioValue �D��x�̍ō��l.
		*/
		void StartGOM(int prioValue);

	public:

		/**
		* ������.
		*/
		void Start();

		/**
		* Update�̑O�ɌĂ΂��X�V.
		*/
		void PreUpdate();

		/**
		* �X�V.
		*/
		void Update();

		/**
		* Update�̌�ɌĂ΂��X�V.
		*/
		void PostUpdate();

		/**
		* Render�̑O�ɌĂ΂��`��.
		*/
		void PreRender();

		/**
		* �`��.
		*/
		void Render();

		/**
		* �|�X�g�G�t�F�N�g�̌�ɌĂ΂��`��.
		*/
		void PostRender();

		/**
		* deleteObjectArray�ɓo�^����Ă���GameObject���폜����.
		*/
		void Delete();

		/**
		* �Q�[���I�u�W�F�N�g���X�g���擾.
		*/
		const vector<list<IGameObject*>>& GetGameObjectList() const
		{
			return GameObjectList_;
		}

		/**
		* GameObject�o�^.
		*
		* @tparam TGO IGameObject���p�������N���X.
		* @param prio �D��x.
		*
		* @return Null if it fails, else a pointer to a T.
		*/
		template<class TGO>
		TGO* NewGameObject(string name, PriorityT prio)
		{
			//�Q�[���I�u�W�F�N�g�쐬
			TGO* newGO = new TGO(name);

			//�R���X�g���N�^�AStart�Ԃ̏�����
			newGO->Awake();

			//�D��x�ݒ�
			newGO->SetPriority(prio);

			//List�ɒǉ�
			GameObjectList_.at(prio).push_back(newGO);

			return newGO;
		}

		/**
		* GameObjectManager����폜����GameObject��o�^����.
		*
		* @param [in,out] go If none-null, the go.
		*/
		void DeleteGameObject(IGameObject* go)
		{
			//�폜List�ɒǉ�
			DeleteObjectList_.push_back(go);
		}

		/**
		* �Q�[���I�u�W�F�N�g�擾.
		*/
		IGameObject* FindGameObject(string name)
		{
			for (auto& objList : GameObjectList_)
			{
				auto go = find_if(objList.begin(), objList.end(), [name](IGameObject* go) { return go->GetName() == name; });
				if (go != objList.end())
				{
					return (*go);
				}
			}
			return nullptr;
		}

		/**
		* �S�폜SceneManager�ɌĂ΂��.
		* isStatic��true�̏ꍇ������Ȃ�.
		*/
		void AllDelete();

		/**
		* �S�폜.
		* isStatic��true�̏ꍇ�ł�����.
		*/
		void Release()
		{
			//�C�e���[�^�擾
			auto& itList = GameObjectList_.begin();
			while (itList != GameObjectList_.end())
			{
				itList->clear();
				itList++;
			}
		}
		
	private:

		/** 1�D��x��1List. */
		using GameObjectListT = list<IGameObject*>;
		/** �o�^����Ă���GameObject. */
		vector<GameObjectListT> GameObjectList_;
		/** �폜����GameObject. */
		GameObjectListT DeleteObjectList_;
		/** �D��x�̍ő�l��ݒ�. */
		PriorityT PriorityMax_;
		/** �D��x�̍ő�l. */
		static const PriorityT MAX_Priority = 255;

	};

	/**
	* �Q�[���I�u�W�F�N�g�Ǘ��N���X���擾.
	*
	* @return A reference to a GameObjectManagerSingleton.
	*/
	static GameObjectManagerSingleton& GameObjectManager()
	{
		return GameObjectManagerSingleton::GetInstance();
	}

	/**
	* �Q�[���I�u�W�F�N�g�쐬�o�^.
	*
	* @tparam TGO Type of the tgo.
	* @param prio (Optional) The prio.
	*
	* @return Null if it fails, else a pointer to a TGO.
	*/
	template<class TGO>
	static TGO* NewGO(string name = "GameObject", PriorityT prio = 0)
	{
		return GameObjectManager().NewGameObject<TGO>(name, prio);
	}

	/**
	* �Q�[���I�u�W�F�N�g�폜�o�^.
	*
	* @param [in,out] go If non-null, the go.
	*/
	static void DeleteGO(IGameObject* go)
	{
		GameObjectManager().DeleteGameObject(go);
	}

}