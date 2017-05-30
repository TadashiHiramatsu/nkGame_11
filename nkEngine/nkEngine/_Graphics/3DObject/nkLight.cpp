/**
 * ライトクラスの実装.
 */
#include"nkstdafx.h"
#include"nkLight.h"

namespace nkEngine
{

	/**
	 * コンストラクタ.
	 */
	Light::Light()
	{
		//ディフューズライト方向
		DiffuseLightDirection_[0] = Vector4::Zero;
		DiffuseLightDirection_[1] = Vector4::Zero;
		DiffuseLightDirection_[2] = Vector4::Zero;
		DiffuseLightDirection_[3] = Vector4::Zero;
		DiffuseLightDirection_[4] = Vector4::Zero;
		DiffuseLightDirection_[5] = Vector4::Zero;

		//ディフューズライト色
		DiffuseLightColor_[0] = Color::White;
		DiffuseLightColor_[1] = Color::White;
		DiffuseLightColor_[2] = Color::White;
		DiffuseLightColor_[3] = Color::White;
		DiffuseLightColor_[4] = Color::White;
		DiffuseLightColor_[5] = Color::White;

		//環境光の設定
		AmbientLight_ = Vector4(0.2f, 0.2f, 0.2f,1.0f);
		
	}

}