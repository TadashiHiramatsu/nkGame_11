/**
 * �V�[���N���X�̒�`.
 */
#pragma once 

namespace nkEngine
{
	/**
	 * �V�[���̊��N���X.
	 * ���̃N���X���p������V�[���N���X���쐬����
	 * �V�[���}�l�[�W���ɓo�^����K�v������
	 */
	class IScene : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		IScene()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		virtual ~IScene()
		{
		}

	public:

		/**
		 * ������.
		 */
		virtual void Start() = 0;

	};
}
