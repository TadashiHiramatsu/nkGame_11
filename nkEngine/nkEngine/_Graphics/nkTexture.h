/**
* テクスチャクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* テクスチャクラス.
	*/
	class Texture : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		Texture()
		{
		}

		/**
		* デストラクタ.
		*/
		~Texture()
		{
		}

		/**
		* 読み込み.
		*
		* @param fileName	ファイル名.
		*/
		bool Load(string fileName);

		/**
		* テクスチャのSRVを取得.
		*/
		ShaderResourceView& GetTextureSRV()
		{
			return TextureSRV_;
		}

	private:

		/** テクスチャメタデータ. */
		DirectX::TexMetadata DXTexMetaData_;
		/** */
		DirectX::ScratchImage DXScratchImage_;
		/** テクスチャのSRV. */
		ShaderResourceView TextureSRV_;

	};

}