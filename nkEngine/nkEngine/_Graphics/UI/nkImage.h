/**
* �摜�`��N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* �摜�`��N���X.
	*/
	class Image : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		Image()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~Image()
		{
		}

		/**
		* �ǂݍ���.
		*/
		void Load(string fileName);

	private:

		/** �e�N�X�`��. */
		Texture Texture_;


	};

}