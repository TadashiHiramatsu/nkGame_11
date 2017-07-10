/**
* FPS�\���E�B���h�E�N���X�̒�`.
*/
#pragma once

#include"Base\nkDebugWindow.h"

namespace nkEngine
{
	
	/**
	* FPS�\���E�B���h�E�N���X.
	*/
	class FPSWindow : public IDebugWindow
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		FPSWindow()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~FPSWindow()
		{
		}

		/**
		* ������.
		*/
		void Start()override;

		/**
		* �`��.
		*/
		void Render()override;

	private:

		/** FPS���X�g. */
		vector<float> FPSList_;

	};

}