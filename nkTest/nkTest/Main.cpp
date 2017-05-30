/**
* メイン関数の実装.
*/
#include"stdafx.h"

/*****************************************************************************************/
#include"Main\MainScene.h"


/**
* エンジンの初期化.
*/
bool InitEngine(HINSTANCE hInstance)
{
	//初期化パラメータ.
	InitParamS initParam;
	initParam.hInstance_ = hInstance;
	initParam.GameName_ = "nkTest";
	initParam.ScreenBufferW_ = 1200;
	initParam.ScreenBufferH_ = 675;
	initParam.FrameBufferW_ = initParam.ScreenBufferW_ * 2;
	initParam.FrameBufferH_ = initParam.ScreenBufferH_ * 2;

	//エンジンの初期化.
	return Engine().Init(initParam);
}

/**
* WindowMain関数.
*
* @param hInstance	    インスタンスハンドル.
* @param hPrevInstance The previous instance.
* @param lpCmdLine	    コマンドライン.
* @param nCmdshow	    コマンドショー.
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow)
{
	//エンジンの初期化.
	if (!InitEngine(hInstance))
	{
		NK_ASSERT(false, "初期化できなかったんだけど.");
		return 0;
	}

	//メインシーンの登録.
	SceneManager().ChangeScene<MainScene>();

	//メインループの実行.
	Engine().RunMainLoop();

	return 0;
}