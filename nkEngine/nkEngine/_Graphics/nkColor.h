/**
* �J���[�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �J���[�N���X.
	*/
	class Color : public Vector4
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Color()
		{
		}

		/**
		* �R���X�g���N�^.
		*/
		Color(float r, float g, float b, float a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		/**
		* �f�X�g���N�^.
		*/
		~Color()
		{
		}

	public:

		/** ��. */
		static const Color Red;
		/** ��. */
		static const Color Green;
		/** ��. */
		static const Color Blue;
		/** ��. */
		static const Color Yellow;
		/** ��. */
		static const Color Purple;
		/** ��. */
		static const Color White;
		/** ��. */
		static const Color Black;

		/** ����. */
		static const Color Transparent;

	};

}