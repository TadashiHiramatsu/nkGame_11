/**
* �Q�[���I�u�W�F�N�g�\���E�B���h�E�N���X�̒�`.
*/
#pragma once

#include"Base\nkDebugWindow.h"

namespace nkEngine
{

	/**
	* �Q�[���I�u�W�F�N�g�\���E�B���h�E�N���X.
	*/
	class GameObjectWindow : public IDebugWindow
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		GameObjectWindow()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~GameObjectWindow()
		{
		}

		/**
		* �`��.
		*/
		void Render()override;

	private:

	};
}