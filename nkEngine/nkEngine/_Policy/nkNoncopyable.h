/**
* NoncopyPolicy�N���X�̒�`.
*/
#pragma once

namespace nkEngine
{

	/**
	* NoncopyPolicy�N���X.
	* �N���X�̃R�s�[���֎~����N���X.
	*/
	class Noncopyable
	{
	public:

		/**
		* �f�t�H���g�R���X�g���N�^.
		*/
		Noncopyable() = default;

		/**
		* �R�s�[�R���X�g���N�^.
		* �폜.
		*/
		Noncopyable(const Noncopyable&) = delete;

		/**
		* ���operator���Z�q.
		* �폜.
		*/
		Noncopyable& operator=(const Noncopyable&) = delete;

	};

}