/**
* テクスチャクラスの実装.
*/
#include"nkstdafx.h"
#include"nkTexture.h"

namespace nkEngine
{

	namespace
	{

		/**
		* 拡張子を特定.
		*/
		string ExtSearch(const string& str)
		{
			stringstream ss(str);
			string buffer;
			while (getline(ss, buffer, '.'));
			return buffer;
		}

	}

	/**
	* 読み込み.
	*
	* @param fileName	ファイル名.
	*/
	bool Texture::Load(string fileName)
	{
		string ext = ExtSearch(fileName);

		HRESULT hr = S_OK;

		string filePathString = "Asset/Texture/" + fileName;

		setlocale(LC_CTYPE, "jpn");

		const char* text= filePathString.c_str();
		wchar_t filePath[256];
		mbstowcs(filePath, text, 256);

		if (ext == "dds" || ext == "DDS")
		{
			//DDS.
			hr = DirectX::LoadFromDDSFile(filePath, 0, &DXTexMetaData_, DXScratchImage_);
		}
		else if (ext == "tga" || ext == "TGA")
		{
			//TGA.
			hr = DirectX::LoadFromTGAFile(filePath, &DXTexMetaData_, DXScratchImage_);
		}
		else
		{
			//その他.
			hr = DirectX::LoadFromWICFile(filePath, 0, &DXTexMetaData_, DXScratchImage_);
		}


		if (FAILED(hr))
		{
			//読み込み失敗.
			static char errorMessage[1024];
			sprintf(errorMessage, "テクスチャの読み込みに失敗しました。%s\n", fileName.c_str());
			NK_ASSERT(false, errorMessage);

			return false;
		}

		TextureSRV_.Create(DXTexMetaData_, DXScratchImage_);

		return true;
	}

}