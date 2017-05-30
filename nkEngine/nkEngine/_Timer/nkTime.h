/**
 * �^�C���N���X�̒�`.
 */
#pragma once

#include"nkStopwatch.h"

namespace nkEngine
{
	/**
	 * �^�C���N���X.
	 * �V���O���g���N���X.
	 */
	class TimeSingleton : Noncopyable
	{
	private:

		/**
		 * �R���X�g���N�^.
		 */
		TimeSingleton()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~TimeSingleton()
		{
		}

	public:

		/**
		 * �C���X�^���X���擾.
		 *
		 * @return	The instance.
		 */
		static TimeSingleton& GetInstance()
		{
			static TimeSingleton instance;
			return instance;
		}

		/**
		 * 1�t���[���̌o�ߎ��Ԃ��擾.
		 *
		 * @return	A float.
		 */
		float DeltaTime() const
		{
			return min(1.0f / 10.0f, FrameDeltaTime_);
		}

		/**
		* FPS�̎擾.
		*/
		float GetFPS() const
		{
			return FPS_;
		}

		/**
		 * �X�V.
		 */
		void Update()
		{
			if (isReady_) 
			{
				sw_.Stop();
				FrameDeltaTime_ = (float)sw_.GetElapsed();
				FPS_ = 1000.0f / (float)sw_.GetElapsedMillisecond();
			}
			sw_.Start();
			isReady_ = true;
		}

	private:
		
		/** 1�t���[���̌o�ߎ���. */
		float FrameDeltaTime_ = 0.0f;
		/** FPS. */
		float FPS_ = 0.0f;
		/** �X�g�b�v�E�H�b�`. */
		Stopwatch sw_;
		/** �v�����n�܂��Ă��邩�t���O. */
		bool isReady_ = false;

	};

	/**
	 * �^�C���N���X�̃C���X�^���X���擾.
	 *
	 * @return	�C���X�^���X.
	 */
	static TimeSingleton& Time()
	{
		return TimeSingleton::GetInstance();
	}

}