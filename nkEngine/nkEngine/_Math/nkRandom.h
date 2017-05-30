/**
* ランダムクラスの定義.
*/
#pragma once

#include <time.h>

namespace nkEngine
{

	/**
	* ランダムクラス.
	* シングルトンクラス.
	*/
	class RandomSingleton : Noncopyable
	{
	private:

		/**
		* コンストラクタ.
		*/
		RandomSingleton()
		{
		}

		/**
		* デストラクタ.
		*/
		~RandomSingleton()
		{
		}

	public:

		/**
		* インスタンスを取得.
		*/
		static RandomSingleton& GetInstance()
		{
			static RandomSingleton instance;
			return instance;
		}

		/**
		* min(この値を含む)とmax(この値を含む)の範囲のランダムなfloat型の数を返します.
		*/
		float Range(float min, float max)
		{
			return min + ((float)GetRandInt() * (max - min) / (1.0 + 0xffffffffUL));
		}

		/** 
		* min(この値を含む)とmax(この値を含む)の範囲のランダムなint型の数を返します.
		*/
		int Range(int min, int max)
		{
			return min + (GetRandInt() % (max - min + 1));
		}

		/** 
		* 0.0(この値を含む)と1.0(この値を含む)の範囲のランダムな数を返します.
		*/
		double value()
		{
			return GetRandInt() * (1.0 / 4294967295.0);
		}

	private:

		/**
		* 初期化.
		*/
		void Init(unsigned long seed)
		{
			mt[0] = seed & 0xffffffffUL;
			for (mti = 1; mti < N; mti++)
			{
				mt[mti] = (1812433253UL * (mt[mti - 1] ^ (mt[mti - 1] >> 30)) + mti);

				mt[mti] &= 0xffffffffUL;

			}
		}

		/**
		* 0～0xffffffffの擬似乱数を返す.
		*/
		__inline unsigned long GetRandInt()
		{
			unsigned long y;
			static unsigned long mag01[2] = { 0x0UL, MATRIX_A };

			if (mti >= N) 
			{
				int kk;

				if (mti == N + 1)
				{
					Init((unsigned long)time);
				}

				for (kk = 0; kk<N - M; kk++) 
				{
					y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
					mt[kk] = mt[kk + M] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}
				for (; kk<N - 1; kk++) 
				{
					y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
					mt[kk] = mt[kk + (M - N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
				}
				y = (mt[N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
				mt[N - 1] = mt[M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];

				mti = 0;
			}

			y = mt[mti++];

			y ^= (y >> 11);
			y ^= (y << 7) & 0x9d2c5680UL;
			y ^= (y << 15) & 0xefc60000UL;
			y ^= (y >> 18);

			return y;
		}

	private:

		static const unsigned long N = 624;
		static const unsigned long M = 397;
		static const unsigned long MATRIX_A = 0x9908b0dfUL;   
		static const unsigned long UPPER_MASK = 0x80000000UL; 
		static const unsigned long LOWER_MASK = 0x7fffffffUL; 
		unsigned long mt[N];
		int mti = N + 1;

	};

	/**
	* ランダムクラス.
	*/
	static RandomSingleton& Random()
	{
		return RandomSingleton::GetInstance();
	}

}// namespace nkEngine