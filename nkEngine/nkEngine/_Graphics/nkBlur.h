/**
* ブラークラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* ブラークラス.
	*/
	class Blur : Noncopyable
	{
	public:

		/** 
		* 頂点バッファ. 
		*/
		struct VertexBufferS
		{
			Vector4 Pos;	//!< 座標.
			Vector2 Tex;	//!< UV座標.
		};

		/**
		* VSステージの定数バッファ構造体.
		*/
		struct VSConstantBufferS
		{
			Vector2 TexSize_;	//!< テクスチャサイズ.
		};

	public:

		/**
		* コンストラクタ.
		*/
		Blur()
		{
		}

		/**
		* デストラクタ.
		*/
		~Blur()
		{
		}

		/**
		* 作成.
		*
		* @param w		横.
		* @param h		高さ.
		* @param srcSRV	元となるSRV.
		*/
		void Create(
			int w,
			int h,
			ShaderResourceView& srcSRV);

		/**
		* 描画.
		*/
		void Render();

		/**
		* ブラー結果のSRVを取得.
		*/
		ShaderResourceView& GetBlurSRV()
		{
			return BlurRT_[1].GetRenderTargetSRV();
		}

	private:

		/** ブラー結果を書き込むレンダリングターゲット. */
		RenderTarget BlurRT_[2];

		/** 元になるSRV. */
		ShaderResourceView* SrcSRV_ = nullptr;

		/** 元となるテクスチャのサイズ. */
		Vector2 SrcTexSize = Vector2::Zero;

		/** Xブラー頂点シェーダ. */
		Shader VShaderXBlur_;
		/** Yブラー頂点シェーダ. */
		Shader VShaderYBlur_;
		/** ピクセルシェーダ. */
		Shader PShader_;

		/** 頂点バッファ. */
		VertexBuffer VertexBuffer_;

		/** VSステージの定数バッファ. */
		ConstantBuffer VSConstantBuffer_;

	};

}