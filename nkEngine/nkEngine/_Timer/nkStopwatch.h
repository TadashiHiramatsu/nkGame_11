/**
 * �X�g�b�v�E�H�b�`�N���X�̒�`.
 */
#pragma once

namespace nkEngine
{

	/**
	 * �X�g�b�v�E�H�b�`�N���X.
	 */
	class Stopwatch : Noncopyable
	{
	public:

		/**
		 * �R���X�g���N�^.
		 */
		Stopwatch()
		{
		}

		/**
		 * �f�X�g���N�^.
		 */
		~Stopwatch() 
		{
		}

		/**
		 * �v���J�n.
		 */
		void Start()
		{
			::QueryPerformanceCounter((LARGE_INTEGER*)&Begin_);
		}

		/**
		 * �v���I��.
		 */
		void Stop()
		{
			::QueryPerformanceFrequency((LARGE_INTEGER*)&Freq_);
			::QueryPerformanceCounter((LARGE_INTEGER*)&End_);

			Elapsed_ = double(End_ - Begin_) / Freq_;
			ElapsedMill_ = Elapsed_ * 1000.0;
			ElapsedMicro_ = ElapsedMill_ * 1000.0;
		}

		/**
		 * �o�ߎ��Ԃ��擾(�P��:�b).
		 *
		 * @return	�o�ߎ���(�P��:�b).
		 */
		double GetElapsed() const
		{
			return Elapsed_;
		}

		/**
		 * �o�ߎ��Ԃ��擾(�P��:�~���b).
		 *
		 * @return	�o�ߎ���(�P��:�~���b).
		 */
		double GetElapsedMillisecond() const
		{
			return ElapsedMill_;
		}

		/**
		 * �o�ߎ��Ԃ��擾(�P��:�}�C�N���b).
		 *
		 * @return	�o�ߎ���(�P��:�}�C�N���b).
		 */
		double GetElapsedMicrosecond() const
		{
			return ElapsedMicro_;
		}

	private:

		/** The frequency. */
		LONGLONG Freq_ = 0;
		/** The end. */
		LONGLONG End_ = 0;
		/** The begin. */
		LONGLONG Begin_ = 0;
		/** �o�ߎ���(�P�ʁF�b). */
		double Elapsed_ = 0.0;
		/** �o�ߎ���(�P�ʁF�~���b). */
		double ElapsedMill_ = 0.0;
		/** �o�ߎ���(�P�ʁF�}�C�N���b). */
		double ElapsedMicro_ = 0.0;

	};

}