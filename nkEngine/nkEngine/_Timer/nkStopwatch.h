/**
 * ストップウォッチクラスの定義.
 */
#pragma once

namespace nkEngine
{

	/**
	 * ストップウォッチクラス.
	 */
	class Stopwatch : Noncopyable
	{
	public:

		/**
		 * コンストラクタ.
		 */
		Stopwatch()
		{
		}

		/**
		 * デストラクタ.
		 */
		~Stopwatch() 
		{
		}

		/**
		 * 計測開始.
		 */
		void Start()
		{
			::QueryPerformanceCounter((LARGE_INTEGER*)&Begin_);
		}

		/**
		 * 計測終了.
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
		 * 経過時間を取得(単位:秒).
		 *
		 * @return	経過時間(単位:秒).
		 */
		double GetElapsed() const
		{
			return Elapsed_;
		}

		/**
		 * 経過時間を取得(単位:ミリ秒).
		 *
		 * @return	経過時間(単位:ミリ秒).
		 */
		double GetElapsedMillisecond() const
		{
			return ElapsedMill_;
		}

		/**
		 * 経過時間を取得(単位:マイクロ秒).
		 *
		 * @return	経過時間(単位:マイクロ秒).
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
		/** 経過時間(単位：秒). */
		double Elapsed_ = 0.0;
		/** 経過時間(単位：ミリ秒). */
		double ElapsedMill_ = 0.0;
		/** 経過時間(単位：マイクロ秒). */
		double ElapsedMicro_ = 0.0;

	};

}