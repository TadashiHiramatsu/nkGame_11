/**
* シャドウマップクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/** モデル描画クラス. */
	class ModelRender;

	/**
	* シャドウマップクラス.
	*/
	class ShadowMap : Noncopyable
	{
	public:

		/**
		* シャドウレシーバー用パラメータ. 
		*/
		struct ShadowReceiverParamS
		{
		public:

			/** ライトビュー行列. */
			Matrix LVMatrix_ = Matrix::Identity;
			/** ライトプロジェクション行列. */
			Matrix LPMatrix_ = Matrix::Identity;

		};

	public:

		/**
		* コンストラクタ.
		*/
		ShadowMap()
		{
		}

		/**
		* デストラクタ.
		*/
		~ShadowMap()
		{
		}

		/**
		* 作成.
		*/
		void Create();

		/**
		* 更新.
		*/
		void Update();

		/**
		* 描画.
		*/
		void Render();

		/**
		* 解放.
		*/
		void Release();

		/**
		* キャスターをリストに追加.
		*
		* @param model	モデル描画クラス.
		*/
		void Entry(ModelRender* model)
		{
			CasterModelList_.push_back(model);
		}

		/**
		* シャドウマップ用テクスチャのSRVを取得.
		*/
		ShaderResourceView& GetShadowMapSRV()
		{
			return ShadowMapRT_.GetRenderTargetSRV();
		}

		/**
		* シャドウレシーバー用のパラメータを取得.
		*/
		const ShadowReceiverParamS& GetShadowReceiverParam()
		{
			return ShadowReceiverParam_;
		}

		/**
		* 近平面を設定.
		*
		* @param n	ニア.
		*/
		void SetNear(float n)
		{
			Near_ = n;
		}

		/**
		* 遠平面を設定.
		*
		* @param f	ファー.
		*/
		void SetFar(float f)
		{
			Far_ = f;
		}

		/**
		* ライトの視点を設定.
		*
		* @param pos The position.
		*/
		void SetLightPosition(const Vector3& pos)
		{
			LightPosition_ = pos;
		}

		/**
		* ライトの注視点を設定.
		*
		* @param target The target.
		*/
		void SetLightTarget(const Vector3& target)
		{
			LightTarget_ = target;
		}

		/**
		* 頂点シェーダを取得.
		*/
		Shader& GetVShader()
		{
			return VShader_;
		}

		/**
		* ピクセルシェーダを取得.
		*/
		Shader& GetPShader()
		{
			return PShader_;
		}

	private:

		/** 有効フラグ. */
		bool isEnable_ = true;

		/** シャドウマップ用レンダリングターゲット. */
		RenderTarget ShadowMapRT_;
		/** 影を書き込むモデルリスト. */
		vector<ModelRender*> CasterModelList_;
		
		/** シャドウレシーバー用のパラメータ. */
		ShadowReceiverParamS ShadowReceiverParam_;

		/** ライトの視点. */
		Vector3 LightPosition_ = Vector3::Up;
		/** ライトの注視点. */
		Vector3 LightTarget_ = Vector3::Zero;

		/** 近平面. */
		float Near_ = 1.0f;
		/** 遠平面. */
		float Far_ = 100.0f;
		/** アスペクト比. */
		float Aspect_ = 1.0f;
		/** 影を落とす範囲の幅. */
		Vector2 ShadowArea_ = Vector2::Zero;

		/** 頂点シェーダ. */
		Shader VShader_;
		/** ピクセルシェーダ. */
		Shader PShader_;

	};

}