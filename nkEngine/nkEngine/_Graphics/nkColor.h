/**
* カラークラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* カラークラス.
	*/
	class Color : public Vector4
	{
	public:

		/**
		* コンストラクタ.
		*/
		Color()
		{
		}

		/**
		* コンストラクタ.
		*/
		Color(float r, float g, float b, float a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		/**
		* デストラクタ.
		*/
		~Color()
		{
		}

	public:

		/** 赤. */
		static const Color Red;
		/** 緑. */
		static const Color Green;
		/** 青. */
		static const Color Blue;
		/** 黄. */
		static const Color Yellow;
		/** 紫. */
		static const Color Purple;
		/** 白. */
		static const Color White;
		/** 黒. */
		static const Color Black;

		/** 透明. */
		static const Color Transparent;

	};

}