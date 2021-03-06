/**
* 形状の基底クラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* 形状の基底クラス.
	*/
	class IShape : public IComponent
	{
	public:

		/** 
		* 頂点バッファ構造体. 
		*/
		struct VertexBufferS
		{
			Vector4 Pos;
			Vector3 Normal;
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
		};

	public:

		/**
		* コンストラクタ.
		*/
		IShape(IGameObject* go) : 
			IComponent(go)
		{
		}

		/**
		* デストラクタ.
		*/
		virtual ~IShape()
		{
		}

		/**
		* 作成.
		*
		* @param light		ライトのポインタ.
		* @param camera		カメラのポインタ.
		*/
		void Create(Light* light, Camera* camera);

		/**
		* 描画.
		*/
		void Render()override;

	protected:

		/**
		* バッファの作成.
		*/
		virtual void CreateBuffer();
		 
	protected:

		/** 頂点シェーダ. */
		Shader VShader_;
		/** ピクセルシェーダ. */
		Shader PShader_;

		/** 頂点バッファ. */
		VertexBuffer VertexBuffer_;
		/** インデックスバッファ. */
		IndexBuffer IndexBuffer_;
		/** VSステージの定数バッファ. */
		ConstantBuffer VSConstantBuffer_;
		/** PSステージの定数バッファ. */
		ConstantBuffer PSConstantBuffer_;

		/** ライト. */
		Light* Light_ = nullptr;
		/** カメラ. */
		Camera* Camera_ = nullptr;

	};

}