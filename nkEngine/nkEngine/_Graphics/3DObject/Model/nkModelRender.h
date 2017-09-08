/**
* モデル描画クラスの定義.
*/
#pragma once

#include"nkModelData.h"
#include"_Object\Component\nkComponent.h"

namespace nkEngine
{

	/**
	* モデル描画クラス.
	*/
	class ModelRender : public IComponent
	{
	public:

		enum ShaderResourceCodeE
		{
			DiffuseTexture = 0,	//!< ディフューズテクスチャ.
			NormalTexture,		//!< 法線テクスチャ.
			SpecularTexture,	//!< スペキュラテクスチャ.
			ShadowTexture,		//!< 影テクスチャ.
		};

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
			Vector4 CameraDir_;	//!< カメラの視線.
			Vector4 EffectFlag_ = Vector4::Zero;	//!< x:法線マップ, y:スペキュラマップ, z:リムライト.
		};

	public:

		/**
		* コンストラクタ.
		*/
		ModelRender(IGameObject* go) : 
			IComponent(go)
		{
			Name_ = "ModelRender";
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
		void Start(
			Light* light,
			Camera* camera
		);

		/**
		* Render前の描画.
		*/
		void PreRender()override;

		/**
		* 描画.
		*/
		void Render()override;

		/**
		* シャドウマップ描画.
		*/
		void RenderToShadowMap();

		/**
		* リムライトフラグを設定する.
		*/
		void SetLimLight(bool lim)
		{
			IsLimLight_ = lim;
		}

	private:

		/** モデルデータ. */
		ModelData* ModelData_ = nullptr;

		/** トランスフォーム. */
		Transform* Transform_ = nullptr;

		/** 頂点シェーダ. */
		Shader VShader_;
		/** スキン用頂点シェーダ. */
		Shader SkinVShader_;
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

		/** リムライトフラグ. */
		bool IsLimLight_ = false;

	};

}