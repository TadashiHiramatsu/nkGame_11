/**
* シェーダリソースビュークラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* シェーダリソースビュークラス.
	* アダプターパターン?クラス.
	*/
	class ShaderResourceView : Noncopyable 
	{
	public:

		/**
		* コンストラクタ.
		*/
		ShaderResourceView()
		{
		}

		/**
		* デストラクタ.
		*/
		~ShaderResourceView()
		{
			//解放.
			Release();
		}

		/**
		* テクスチャ用のSRVを作成.
		*
		* @param texture	テクスチャ.
		*/
		bool Create(ID3D11Texture2D* texture);

		/**
		* テクスチャ用のSRVを作成.
		*
		* @param meta	テクスチャメタデータ.
		* @param image	スクラッチイメージ.
		*/
		bool Create(DirectX::TexMetadata& meta, DirectX::ScratchImage& image);

		/**
		* 解放.
		* デストラクタで呼んでいる.
		*/
		void Release();

		/**
		* ID3D11ShaderResourceViewを取得.
		*/
		ID3D11ShaderResourceView*& GetBody()
		{
			return D3DSRV_;
		}

	private:

		/** D3D11のSRVクラス. */
		ID3D11ShaderResourceView* D3DSRV_ = nullptr;

	};

}