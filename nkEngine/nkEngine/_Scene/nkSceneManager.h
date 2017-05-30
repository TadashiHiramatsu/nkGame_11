/**
 * �V�[���}�l�[�W���N���X�̒�`.
 */
#pragma once

#include"nkScene.h"

namespace nkEngine
{

	/**
	 * �V�[���}�l�[�W���N���X.
	 * �V���O���g���N���X.
	 * ���̃N���X��IScene�N���X���p�������N���X��o�^����.
	 */
	class SceneManagerSingleton : Noncopyable
	{
	private:

		/**
		 * �R���X�g���N�^.
		 */
		SceneManagerSingleton()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~SceneManagerSingleton()
		{
		}

	public:

		/**
		 * �C���X�^���X�̎擾.
		 *
		 * @return	The instance.
		 */
		static SceneManagerSingleton& GetInstance()
		{
			static SceneManagerSingleton instance;
			return instance;
		}

		/**
		 * IScene�N���X�p���N���X�̏��������Ăяo���� 
		 * GameObjectManager�N���X��������.
		 *
		 * @tparam	TScene	IScene�N���X���p�������N���X.
		 */
		template <class TScene>
		void ChangeScene()
		{
			if (!NextScene_)
			{
				//�V�[���ɐݒ�
				NextScene_ = new TScene();
			}

			isChange_ = true;
		}

		/**
		* �X�V.
		* ���̃V�[�����o�^����Ă�����ύX����.
		*/
		void Update()
		{
			if (isChange_)
			{
				//�o�^����Ă���Q�[���I�u�W�F�N�g��S�폜
				GameObjectManager().AllDelete();

				if (NowScene_)
				{
					delete NowScene_;
				}

				NowScene_ = NextScene_;

				//�V�[���N���X�̏�����
				NowScene_->Start();

				delete NextScene_;
				NextScene_ = nullptr;

				isChange_ = false;
			}
		}

	private:

		bool isChange_ = false;

		/** �V�[���N���X. */
		IScene* NowScene_ = nullptr;
		IScene* NextScene_ = nullptr;

	};

	/**
	 * �V�[���}�l�[�W���[�̎擾.
	 *
	 * @author	HiramatsuTadashi
	 * @date	2017/01/07
	 *
	 * @return	A reference to a SceneManagerSingleton.
	 */
	inline SceneManagerSingleton& SceneManager()
	{
		return SceneManagerSingleton::GetInstance();
	}

}