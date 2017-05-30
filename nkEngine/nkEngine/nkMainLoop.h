/**
* ���C�����[�v�N���X�̒�`.
*/
#pragma once

#include"_Graphics\nkRenderTarget.h"

#include"_Graphics\PreRender\nkShadowMap.h"

namespace nkEngine
{

	/**
	* ���C�����[�v�N���X.
	*/
	class MainLoop : Noncopyable
	{
	public:

		/**
		* �R���X�g���N�^.
		*/
		MainLoop()
		{
		}

		/**
		* �f�X�g���N�^.
		*/
		~MainLoop()
		{
		}

		/**
		* ������.
		*/
		bool Init();

		/**
		* �X�V.
		*/
		void Update();

		/**
		* �`��.
		*/
		void Render();

		/**
		* ���.
		*/
		void Release();

		/**
		* ���C�������_�����O�^�[�Q�b�g��؂�ւ�.
		*/
		void ToggleMainRenderTarget()
		{
			CurrentMainRenderTarget_ ^= 1;
		}

		/**
		* ���C�������_�����O�^�[�Q�b�g���擾.
		*/
		RenderTarget& GetMainRenderTarget()
		{
			return MainRenderTarget_[CurrentMainRenderTarget_];
		}

	private:

		/**
		* ���C�������_�����O�^�[�Q�b�g�̓��e���o�b�N�o�b�t�@�ɃR�s�[.
		*/
		void CopyMainRenderTargetToBackBuffer();

	private:

		/** �I�𒆂̃��C�������_�����O�^�[�Q�b�g. */
		int CurrentMainRenderTarget_ = 0;
		/** ���C�������_�����O�^�[�Q�b�g. */
		RenderTarget MainRenderTarget_[2];

	public:

		/** �V���h�E�}�b�v�N���X. */
		ShadowMap ShadowMap_;

	};

}