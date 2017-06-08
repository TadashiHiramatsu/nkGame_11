/**
* マテリアルクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* マテリアルクラス.
	*/
	class Material : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		Material()
		{
		}

		/**
		* デストラクタ.
		*/
		~Material()
		{
		}

		/**
		* 初期化. 
		*/
		void Init(string textureName);

		/**
		* テクスチャのSRVを取得.
		*/
		ShaderResourceView& GetTextureSRV()
		{
			return Texture_.GetTextureSRV();
		}

		/**
		* 法線マップの有無を取得.
		*/
		bool isNormalMap()
		{
			if (NormalTexture_ != nullptr)
			{
				return true;
			}
			return false;
		}

		/**
		* 法線マップテクスチャのSRVを取得.
		*/
		ShaderResourceView& GetNormalTextureSRV()
		{
			if (NormalTexture_ != nullptr)
			{
				return NormalTexture_->GetTextureSRV();
			}
		}

		/**
		* スペキュラマップの有無を取得.
		*/
		bool isSpecularMap()
		{
			if (SpecularTexture_ != nullptr)
			{
				return true;
			}
			return false;
		}

		/**
		* スペキュラマップテクスチャのSRVを取得.
		*/
		ShaderResourceView& GetSpecularTextureSRV()
		{
			if (SpecularTexture_ != nullptr)
			{
				return SpecularTexture_->GetTextureSRV();
			}
		}

	public:

		/** テクスチャ名. */
		string TextureName_ = "";

		/** テクスチャ. */
		Texture Texture_;

		/** 法線マップテクスチャ. */
		Texture* NormalTexture_ = nullptr;
		/** スペキュラマップテクスチャ. */
		Texture* SpecularTexture_ = nullptr;

	};

}