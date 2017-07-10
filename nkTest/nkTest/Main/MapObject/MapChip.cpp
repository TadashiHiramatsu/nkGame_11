/**
* �}�b�v�`�b�v�N���X�̎���.
*/
#include"stdafx.h"
#include"MapChip.h"

#include"../GameObject/MainCamera.h"
#include"../GameObject/MainLight.h"

/**
* ������.
*/
void MapChip::Start()
{
	//���f���ǂݍ���.
	ModelRender_.Init("MapObject_01", &Transform_, &g_MainLight->GetLight(), &g_MainCamera->GetCamera());
	ModelRender_.SetLimLight(true);
}

/**
* �X�V.
*/
void MapChip::Update()
{
	Transform_.Update();

	ModelRender_.Update();
}

/**
* Render�O�̕`��.
*/
void MapChip::PreRender()
{
	ModelRender_.PreRender();
}

/**
* �`��.
*/
void MapChip::Render()
{
	ModelRender_.Render();
}
