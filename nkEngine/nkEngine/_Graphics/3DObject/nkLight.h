/**
 * ライトクラスの定義
 */
#pragma once

namespace nkEngine
{

	/**
	 * ライトクラス.
	 */
	class Light
	{
	public:

		/**
		 * コンストラクタ.
		 */
		Light();

		/**
		 * デストラクタ.
		 */
		~Light()
		{
		}

		/**
		 * ディフューズライトの向きを設定.
		 *
		 * @param no	   ライトの番号.
		 * @param lightDir ライトの方向、正規化済みベクトル.
		 */
		void SetDiffuseLightDirection(int no, const Vector3& lightDir)
		{
			NK_ASSERT(no < LIGHT_NUM, "ライトの数大杉ぃぃぃ");
			DiffuseLightDirection_[no] = Vector4(lightDir.x, lightDir.y, lightDir.z, 1.0f);
		}

		/**
		 * ディフューズライトの向きを取得.
		 *
		 * @param no ライトの番号.
		 *
		 * @return The diffuse light direction.
		 */
		const Vector4& GetDiffuseLightDirection(int no) const
		{
			return DiffuseLightDirection_[no];
		}

		/**
		 * ディフューズライトの色を設定.
		 *
		 * @param no	   ライトの番号.
		 * @param lightColor ライトの色、0.0f～1.0fの値.
		 */
		void SetDiffuseLightColor(int no, const Vector4& lightColor)
		{
			NK_ASSERT(no < LIGHT_NUM, "ライトの色大杉ぃぃぃ");
			DiffuseLightColor_[no] = lightColor;
		}

		/**
		 * ディフューズライトの色を取得.
		 *
		 * @param no The ライトの番号.
		 *
		 * @return The diffuse light color.
		 */
		const Vector4& GetDiffuseLightColor(int no) const
		{
			return DiffuseLightColor_[no];
		}

		/**
		 * アンビエントライトの強さを設定.
		 *
		 * @param amb アンビエントの色.
		 */
		void SetAmbientLight(const Vector4& amb)
		{
			AmbientLight_ = amb;
		}

		/**
		 * アンビエントライトを取得.
		 *
		 * @return The ambient light.
		 */
		const Vector4& GetAmbientLight() const
		{
			return AmbientLight_;
		}

	public:

		/** ライトの数. */
		static const USHORT LIGHT_NUM = 6;
	
	private:

		/** 平行光源の方向. */
		Vector4 DiffuseLightDirection_[LIGHT_NUM];
		/** 平行光源の色. */
		Vector4	DiffuseLightColor_[LIGHT_NUM];
		/** 環境光. */
		Vector4	AmbientLight_;

	};

}