/**
 * �Q�[���I�u�W�F�N�g�}�l�[�W���N���X�̒�`.
 */
#pragma once

#include"nkGameObject.h"

namespace nkEngine
{

	/**
	 * �Q�[���I�u�W�F�N�g�}�l�[�W��.
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

	public:

		/**
		 * GameObject�o�^.
		 *
		 * @tparam TGO IGameObject���p�������N���X.
		 * @param prio �D��x.
		 *
		 * @return Null if it fails, else a pointer to a T.
		 */
		template<class TGO>
		TGO* NewGameObject(GOPriorityT prio)
		{
			//�Q�[���I�u�W�F�N�g�쐬
			TGO* newGO = new TGO;

			//�R���X�g���N�^�AStart�Ԃ̏�����
			newGO->Awake();

			//�D��x�ݒ�
			newGO->Priority_ = prio;

			//List�ɒǉ�
			GameObjectArray_.at(prio).push_back(newGO);

			return newGO;
		}

		/**
		 * GameObjectManager����폜����GameObject��o�^����.
		 *
		 * @param [in,out] go If non-null, the go.
		 */
		void DeleteGameObject(IGameObject* go)
		{
			//�폜List�ɒǉ�
			DeleteObjectArray_.at(go->GetPriority()).push_back(go);
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
			auto& itList = GameObjectArray_.begin();
			while (itList != GameObjectArray_.end())
			{
				itList->clear();
				itList++;
			}
		}
		
	private:

		/** 1�D��x��1List. */
		typedef list<IGameObject*> GameObjectListT;
		/** �o�^����Ă���GameObject. */
		vector<GameObjectListT> GameObjectArray_;
		/** �폜����GameObject. */
		vector<GameObjectListT> DeleteObjectArray_;
		/** �D��x�̍ő�l��ݒ�. */
		GOPriorityT GOPriorityMax_;
		/** �D��x�̍ő�l. */
		static const GOPriorityT MAX_Priority = 255;

	};

	/**
	 * Game object manager.
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
	static TGO* NewGO(int prio = 0)
	{
		return GameObjectManager().NewGameObject<TGO>(prio);
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