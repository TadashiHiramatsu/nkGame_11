/**
 * タイムクラスの定義.
 */
#pragma once

#include"nkStopwatch.h"

namespace nkEngine
{
	/**
	 * タイムクラス.
	 * シングルトンクラス.
	 */
	class TimeSingleton : Noncopyable
	{
	private:

		/**
		 * コンストラクタ.
		 */
		TimeSingleton()
		{
		}

		/**
		 * デストラクタ.
		 */
		~TimeSingleton()
		{
		}

	public:

		/**
		 * インスタンスを取得.
		 *
		 * @return	The instance.
		 */
		static TimeSingleton& GetInstance()
		{
			static TimeSingleton instance;
			return instance;
		}

		/**
		 * 1フレームの経過時間を取得.
		 *
		 * @return	A float.
		 */
		float DeltaTime() const
		{
			return min(1.0f / 10.0f, FrameDeltaTime_);
		}

		/**
		* FPSの取得.
		*/
		float GetFPS() const
		{
			return FPS_;
		}

		/**
		 * 更新.
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
		
		/** 1フレームの経過時間. */
		float FrameDeltaTime_ = 0.0f;
		/** FPS. */
		float FPS_ = 0.0f;
		/** ストップウォッチ. */
		Stopwatch sw_;
		/** 計測が始まっているかフラグ. */
		bool isReady_ = false;

	};

	/**
	 * タイムクラスのインスタンスを取得.
	 *
	 * @return	インスタンス.
	 */
	static TimeSingleton& Time()
	{
		return TimeSingleton::GetInstance();
	}

}