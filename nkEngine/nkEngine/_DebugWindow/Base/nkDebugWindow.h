/**
* �f�o�b�O�E�B���h�E�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �f�o�b�O�E�B���h�E�N���X.
	*/
	class IDebugWindow : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		IDebugWindow()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		virtual ~IDebugWindow()
		{
		}

		/**
		* ������.
		*/
		virtual void Start()
		{
		}

		/**
		* �`��.
		*/
		virtual void Render() = 0;

		/**
		* �L���t���O��ݒ�.
		*/
		void SetActive(bool is)
		{
			IsActive_ = is;
		}

		/**
		* ���O���擾.
		*/
		const string& GetName() const
		{
			return Name_;
		}

	public:

		/**
		* �`��.
		* �Ǘ��N���X����Ă΂��.
		*/
		void RenderWrapper()
		{
			if (IsActive_)
			{
				Render();
			}
		}

	protected:

		/** ���O. */
		string Name_ = "";

		/** �L���t���O. */
		bool IsActive_ = true;

	};

}