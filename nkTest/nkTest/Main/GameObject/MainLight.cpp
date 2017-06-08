/**
* ���C�����C�g�N���X�̎���.
*/
#include"stdafx.h"
#include"MainLight.h"

/**
* ������.
*/
void MainLight::Start()
{

	Light_.SetDiffuseLightColor(0, Vector4(0.6f, 0.6f, 0.6f, 1.0f));

	Light_.SetAmbientLight(Vector4(0.5f, 0.5f, 0.5f, 1.0f));
	
	Vector3 dld = Vector3(1.0f, -1.0f, 1.0f);
	dld.Normalize();
	Light_.SetDiffuseLightDirection(0, dld);

}

/**
* �X�V.
*/
void MainLight::Update()
{
	static float angle = 0;
	Vector3 dld = Vector3(1.0f, -0.5f, 1.0f);
	dld.Normalize();
	Matrix mTmp = Matrix::Identity;
	mTmp.MakeRotationY(angle);
	dld.TransformCoord(mTmp);
	Light_.SetDiffuseLightDirection(0, dld); 
	dld.Scale(-10);
	Engine().GetShadowMap().SetLightPosition(dld);

	angle += 0.3f;
}
