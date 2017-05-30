/**
* ���C���֐��̎���.
*/
#include"stdafx.h"

/*****************************************************************************************/
#include"Main\MainScene.h"


/**
* �G���W���̏�����.
*/
bool InitEngine(HINSTANCE hInstance)
{
	//�������p�����[�^.
	InitParamS initParam;
	initParam.hInstance_ = hInstance;
	initParam.GameName_ = "nkTest";
	initParam.ScreenBufferW_ = 1200;
	initParam.ScreenBufferH_ = 675;
	initParam.FrameBufferW_ = initParam.ScreenBufferW_ * 2;
	initParam.FrameBufferH_ = initParam.ScreenBufferH_ * 2;

	//�G���W���̏�����.
	return Engine().Init(initParam);
}

/**
* WindowMain�֐�.
*
* @param hInstance	    �C���X�^���X�n���h��.
* @param hPrevInstance The previous instance.
* @param lpCmdLine	    �R�}���h���C��.
* @param nCmdshow	    �R�}���h�V���[.
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow)
{
	//�G���W���̏�����.
	if (!InitEngine(hInstance))
	{
		NK_ASSERT(false, "�������ł��Ȃ������񂾂���.");
		return 0;
	}

	//���C���V�[���̓o�^.
	SceneManager().ChangeScene<MainScene>();

	//���C�����[�v�̎��s.
	Engine().RunMainLoop();

	return 0;
}