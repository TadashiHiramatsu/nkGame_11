/**
* モデル描画クラスの定義.
*/
#pragma once

#include"nkModelData.h"

namespace nkEngine
{

	/**
	* モデル描画クラス.
	*/
	class ModelRender : Noncopyable
	{
	public:

		/**
		* VSステージの定数バッファ構造体.
		*/
		struct VSConstantBufferS
		{
			Matrix WorldMatrix_;	//!< ワールド行列.
			Matrix ViewMatrix_;		//!< ビュー行列.
			Matrix ProjMatrix_;		//!< プロジェクション行列.
		};

		/**
		* PSステージの定数バッファ構造体.
		*/
		struct PSConstantBufferS
		{
			Light Light_;	//!< ライト.
			ShadowMap::ShadowReceiverParamS SRP_;	//!< シャドウレシーバー用パラメータ.
			Vector4 CameraPos_;	//!< カメラポジション.
			Vector4 EffectFlag_ = Vector4::Zero;	//!< x:法線マップ, y:スペキュラマップ.
		};

	public:

		/**
		* コンストラクタ.
		*/
		ModelRender()
		{
		}

		/**
		* デストラクタ.
		*/
		~ModelRender()
		{
		}

		/**
		* 初期化.
		*/
		void Init(
			string fileName,
			Transform* parent,
			Light* light,
			Camera* camera
		);

		/**
		* 更新.
		*/
		void Update();

		/**
		* Render前の描画.
		*/
		void PreRender();

		/**
		* 描画.
		*/
		void Render();

		/**
		* シャドウマップ描画.
		*/
		void RenderToShadowMap();

		/**
		* モデルデータを取得.
		*/
		ModelData& GetModelData()
		{
			return ModelData_;
		}

	private:

		/** モデルデータ. */
		ModelData ModelData_;

		/** トランスフォーム. */
		Transform* Transform_ = nullptr;

		/** 頂点シェーダ. */
		Shader VShader_;
		/** ピクセルシェーダ. */
		Shader PShader_;

		/** VSステージの定数バッファ. */
		ConstantBuffer VSConstantBuffer_;
		/** PSステージの定数バッファ. */
		ConstantBuffer PSConstantBuffer_;

		/** サンプラステート. */
		SamplerState SamplerState_;

		/** ライトのポインタ. */
		Light* Light_ = nullptr;
		/** カメラのポインタ. */
		Camera* Camera_ = nullptr;

	};

}