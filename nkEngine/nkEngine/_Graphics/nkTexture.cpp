/**
* �e�N�X�`���N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkTexture.h"

namespace nkEngine
{

	namespace
	{

		/**
		* �g���q�����.
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
	* �ǂݍ���.
	*
	* @param fileName	�t�@�C����.
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
			//���̑�.
			hr = DirectX::LoadFromWICFile(filePath, 0, &DXTexMetaData_, DXScratchImage_);
		}


		if (FAILED(hr))
		{
			//�ǂݍ��ݎ��s.
			static char errorMessage[1024];
			sprintf(errorMessage, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B%s\n", fileName.c_str());
			NK_ASSERT(false, errorMessage);

			return false;
		}

		TextureSRV_.Create(DXTexMetaData_, DXScratchImage_);

		return true;
	}

}