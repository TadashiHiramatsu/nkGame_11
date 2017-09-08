/**
* メインライトクラスの実装.
*/
#include"stdafx.h"
#include"MainLight.h"

/**
* 初期化.
*/
void MainLight::Start()
{

	Light_.SetDiffuseLightColor(0, Vector4(0.8f, 0.8f, 0.8f, 1.0f));

	//Light_.SetAmbientLight(Vector4(233.0f / 255.0f, 51.0f / 255.0f, 11.0f / 255.0f, 1.0f));
	Light_.SetAmbientLight(Vector4(0.5f, 0.5f, 0.5f, 1.0f));
	
	Vector3 dld = Vector3(1.0f, -1.0f, 1.0f);
	dld.Normalize();
	Light_.SetDiffuseLightDirection(0, dld);

	dld.Scale(-10);
	Engine().GetShadowMap().SetLightPosition(dld);


}

/**
* 更新.
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
