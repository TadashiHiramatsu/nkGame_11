/**
* シェーダクラスの定義.
*/
#pragma once

namespace nkEngine
{

	/**
	* シェーダクラス.
	*/
	class Shader : Noncopyable
	{
	public:

		/**
		* シェーダタイプ.
		*/
		enum class TypeE
		{
			NONE = -1,	//!< 未読み込み.
			VS,			//!< 頂点シェーダ.
			PS,			//!< ピクセルシェーダ.
		};

	public:

		/**
		* コンストラクタ.
		*/
		Shader()
		{
		}

		/**
		* デストラクタ.
		*/
		~Shader() 
		{
			Release();
		}

		/**
		* 読み込み.
		*
		* @param fileName	ファイル名.
		* @param entryName	エントリーポインタとなる関数の名前.
		* @param type		シェーダタイプ.
		*/
		bool Load(string fileName, const char* entryName, TypeE type);

		/**
		* 解放.
		*/
		void Release();

		/**
		* シェーダの取得.
		*/
		void* GetBody()
		{
			return Shader_;
		}

		/**
		* インプットレイアウトの取得.
		*/
		ID3D11InputLayout* GetInputLayout()
		{
			return InputLayout_;
		}

	private:

		/**
		* ファイルの読み込み.
		*
		* @param filePath	ファイルパス.
		* @param readBuffer	読み込み先バッファ.
		* @param fileSize	ファイルサイズ.
		*/
		void ReadFile(const char* filePath, char* readBuffer, int& fileSize);

		/**
		* 頂点シェーダーから頂点レイアウトを生成.
		*
		* @param pShaderBlob	コンパイル済みシェーダへのポインタ.
		* @param pInputLayout	インプットレイアウトの出力先.
		*/
		HRESULT CreateInputLayout(ID3DBlob* pShaderBlob, ID3D11InputLayout** pInputLayout);

	private:

		/** シェーダタイプ. */
		TypeE ShaderType_ = TypeE::NONE;
		/** シェーダ. */
		void* Shader_ = nullptr;
		/** インプットレイアウト. */
		ID3D11InputLayout* InputLayout_ = nullptr;

	};
}