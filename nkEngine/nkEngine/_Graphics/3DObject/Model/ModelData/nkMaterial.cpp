/**
* マテリアルクラスの実装.
*/
#include"nkstdafx.h"
#include"nkMaterial.h"

namespace nkEngine
{

	namespace
	{

		/**
		* ファイル名を特定.
		*/
		vector<string> FileNameSearch(const string& str)
		{
			stringstream ss(str);
			string buffer;
			vector<string> fileName;
			while (getline(ss, buffer, '.'))
			{
				fileName.push_back(buffer);
			}
			return fileName;
		}

	}

	/**
	* 初期化.
	*/
	void Material::Init(string textureName)
	{

		Name_ = textureName;

		string filePath = "Model/" + Name_;

		Texture_.Load(filePath);

		vector<string> fileName = FileNameSearch(Name_);

		string normalFileName = "Model/" + fileName[0] + "_Normal." + fileName[1];

		string normalFilePath = "Asset/Texture/" + normalFileName;
		
		if (PathFileExists(normalFilePath.c_str()))
		{
			NormalTexture_ = new Texture();
			NormalTexture_->Load(normalFileName);
		}

		string specularFileName = "Model/" + fileName[0] + "_Specular." + fileName[1];

		string specularFilePath = "Asset/Texture/" + specularFileName;

		if (PathFileExists(specularFilePath.c_str()))
		{
			SpecularTexture_ = new Texture();
			SpecularTexture_->Load(specularFileName);
		}

	}

}