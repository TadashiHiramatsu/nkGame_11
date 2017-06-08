/**
* 画像描画クラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* 画像描画クラス.
	*/
	class Image : Noncopyable
	{
	public:

		/**
		* コンストラクタ.
		*/
		Image()
		{
		}

		/**
		* デストラクタ.
		*/
		~Image()
		{
		}

		/**
		* 読み込み.
		*/
		void Load(string fileName);

	private:

		/** テクスチャ. */
		Texture Texture_;


	};

}