/**
* メインシーンクラスの実装.
*/
#include"stdafx.h"
#include"MainScene.h"

/*******************************************************/

//カメラ.
#include"GameObject\MainCamera.h"
MainCamera* g_MainCamera = nullptr;
#include"GameObject\MainLight.h"
MainLight* g_MainLight = nullptr;

#include"GameObject\TestObject.h"
#include"Player\UnityChan.h"
#include"MapObject\Ground.h"
#include"MapObject\MapChip.h"

/**
* 初期化.
*/
void MainScene::Start()
{
	g_MainCamera = NewGO<MainCamera>();
	g_MainLight = NewGO<MainLight>();
	
	NewGO<UnityChan>();
	NewGO<Ground>();

	//NewGO<MapChip>();

}
