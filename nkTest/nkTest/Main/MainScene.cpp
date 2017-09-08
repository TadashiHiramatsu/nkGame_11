/**
* メインシーンクラスの実装.
*/
#include"stdafx.h"
#include"MainScene.h"

/*******************************************************/

//カメラ.
#include"GameObject\MainCamera.h"
#include"GameObject\MainLight.h"

#include"Player\CandyRockStar.h"
#include"MapObject\Ground.h"
#include"MapObject\MapChip.h"

/**
* 初期化.
*/
void MainScene::Start()
{
	NewGO<MainCamera>("MainCamera");
	NewGO<MainLight>("MainLight");
	
	NewGO<CandyRockStar>("CandyRockStar");
	NewGO<Ground>("Ground");
	//NewGO<MapChip>("MapChip");

}
