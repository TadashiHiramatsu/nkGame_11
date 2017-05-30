/**
* シェーダクラスの実装.
*/
#include"nkstdafx.h"
#include"nkShader.h"

namespace nkEngine
{

	/**
	* 読み込み.
	*
	* @param fileName	ファイル名.
	* @param entryName	エントリーポインタとなる関数の名前.
	* @param type		シェーダタイプ.
	*/
	bool Shader::Load(string fileName, const char* entryName, TypeE type)
	{
		Release();
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
		//デバック状態.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		//コンパイル済みシェーダー.
		ScopedResource<ID3DBlob> blobOut;
		//エラーメッセージ.
		ScopedResource<ID3DBlob> errorBlob;

		//シェーダタイプ.
		ShaderType_ = type;

		//シェーダテキスト.
		static char text[5 * 1024 * 1024];

		//シェーダサイズ.
		int fileSize = 0;

		string filePath = "Asset/Shader/" + fileName + ".fx";

		//シェーダーをロード。
		ReadFile(filePath.c_str(), text, fileSize);

		//シェーダモデル名.
		static const char* shaderModelNames[] = 
		{
			"vs_5_0",
			"ps_5_0",
			"cs_5_0"
		};

		hr = D3DCompile(
			text,	//未コンパイルのシェーダデータへのポインタ.
			fileSize,	//シェーダデータのサイズ.
			nullptr,	//(省略可能)シェーダファイル名.
			nullptr,	//(省略可能)終端マクロ定義の配列.
			nullptr,	//(省略可能)ID3D10Includeへのポインタ.(シェーダファイルにインクルードがあるとここがnullptrじゃだめ.)
			entryName,	//エントリー関数の名前.
			shaderModelNames[(int)ShaderType_],	//シェーダ機能セットです.
			dwShaderFlags,	//シェーダのコンパイルオプション.
			0,	//エフェクトのコンパイルオプション.
			&blobOut.res,	//コンパイルされたコードを格納するID3D10Blobのアドレス.
			&errorBlob.res	//(省略可能)コンパイルのエラーメッセージを格納するID3D10Blobのアドレス.
		);
		if (FAILED(hr))
		{
			//エラーコードを出力.
			if (errorBlob.res != nullptr) 
			{
				static char errorMessage[10 * 1024];
				sprintf(errorMessage, "filePath : %s, %s", filePath.c_str(), errorBlob.res->GetBufferPointer());
				MessageBox(NULL, errorMessage, "シェーダーコンパイルエラー", MB_OK);
			}

			return false;
		}

		//デバイスの取得.
		ID3D11Device* Device = Engine().GetDevice();

		//シェーダタイプ事の処理.
		switch (ShaderType_)
		{
		case TypeE::VS:
		{
			//頂点シェーダー.
			hr = Device->CreateVertexShader(
				blobOut.res->GetBufferPointer(),	//コンパイル済みシェーダへのポインタ.
				blobOut.res->GetBufferSize(),	//コンパイル済み頂点シェーダのサイズ.
				nullptr,	//クラスリンクインターフェイスへのポインタ.
				(ID3D11VertexShader**)&Shader_	//ID3D11VertexShaderインターフェイスへのポインタ.
			);
			if (FAILED(hr)) 
			{
				return false;
			}
			
			//入力レイアウトを作成。
			hr = CreateInputLayout(blobOut.res, &InputLayout_);
			if (FAILED(hr))
			{
				//入力レイアウトの作成に失敗した.
				return false;
			}

		}
		break;
		case TypeE::PS:
		{
			//ピクセルシェーダー.
			hr = Device->CreatePixelShader(
				blobOut.res->GetBufferPointer(),	//コンパイル済みシェーダへのポインタ.
				blobOut.res->GetBufferSize(),	//コンパイル済みピクセルシェーダのサイズ.
				nullptr,	//クラスリンクインターフェイスへのポインタ.
				(ID3D11PixelShader**)&Shader_	//ID3D11VertexShaderインターフェイスへのポインタ.
			);
			if (FAILED(hr)) 
			{
				return false;
			}

		}
		break;
		}

		return true;

	}

	/**
	* 解放.
	*/
	void Shader::Release()
	{
		if (Shader_ != nullptr) 
		{
			//シェーダタイプ事の解放.
			switch (ShaderType_)
			{
			case TypeE::VS:
				((ID3D11VertexShader*)Shader_)->Release();
				break;
			case TypeE::PS:
				((ID3D11PixelShader*)Shader_)->Release();
				break;
			}
			Shader_ = nullptr;
		}

		if (InputLayout_ != nullptr)
		{
			//インプットレイアウトの解放.
			InputLayout_->Release();
			InputLayout_ = nullptr;
		}

	}

	/**
	* ファイルの読み込み.
	*
	* @param filePath	ファイルパス.
	* @param readBuffer	読み込み先バッファ.
	* @param fileSize	ファイルサイズ.
	*/
	void Shader::ReadFile(const char * filePath, char * readBuffer, int & fileSize)
	{
		//ファイル読み込み.
		FILE* fp = fopen(filePath, "rb");
		fseek(fp, 0, SEEK_END);
		fpos_t fPos;
		fgetpos(fp, &fPos);
		fseek(fp, 0, SEEK_SET);
		fileSize = (int)fPos;
		//バッファに書き込み
		fread(readBuffer, fileSize, 1, fp);
		fclose(fp);
	}

	/**
	* 頂点シェーダーから頂点レイアウトを生成.
	*
	* @param pShaderBlob	コンパイル済みシェーダへのポインタ.
	* @param pInputLayout	インプットレイアウトの出力先.
	*/
	HRESULT Shader::CreateInputLayout(ID3DBlob * pShaderBlob, ID3D11InputLayout** pInputLayout)
	{

		HRESULT hr = S_OK;

		//反射インターフェイスへのポインタ.
		ID3D11ShaderReflection* pVertexShaderReflection;
		
		//シェーダ情報からリフレクションを行う.
		hr = D3DReflect(
			pShaderBlob->GetBufferPointer(),	//コンパイル済みシェーダへのポインタ.
			pShaderBlob->GetBufferSize(),	//コンパイル済み頂点シェーダのサイズ.
			IID_ID3D11ShaderReflection,	//使用するCOMインターフェイスの参照GUID.
			(void**)&pVertexShaderReflection	//反射インターフェイスへのポインタ.
		);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		D3D11_SHADER_DESC shaderDesc;
		pVertexShaderReflection->GetDesc(&shaderDesc);

		//入力情報リスト.
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

		for (UINT i = 0; i < shaderDesc.InputParameters; i++)
		{
			//インプット情報.
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

			//エレメント定義を設定.
			D3D11_INPUT_ELEMENT_DESC elementDesc;
			elementDesc.SemanticName = paramDesc.SemanticName;	//シェーダー入力署名でこの要素に関連付けられているHLSLセマンティクス.
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;	//要素のセマンティクスインデックス.(4x4 のマトリクスには 4 個の構成要素があり、それぞれの構成要素にはセマンティクス名として matrix が付けられますが、4 個の構成要素にはそれぞれ異なるセマンティクス インデックス (0、1、2、3) が割り当てられます.)
			elementDesc.InputSlot = 0;	//入力アセンブラーを識別する整数値.
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;	//(省略可能)各要素間のオフセット(バイト単位).

			//インスタンシング用データ.
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	//単一の入力スロットの入力データクラスを識別.
			elementDesc.InstanceDataStepRate = 0;	//バッファーの中で要素の 1 つ分進む前に、インスタンス単位の同じデータを使用して描画するインスタンスの数.

			//フォーマットの設定.

			if (paramDesc.Mask == 1) //1次元ベクトル.
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32_UINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32_SINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
				}
			}
			else if (paramDesc.Mask <= 3) //2次元ベクトル.
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
				}
			}
			else if (paramDesc.Mask <= 7) //3次元ベクトル.
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
				}
			}
			else if (paramDesc.Mask <= 15) //4次元ベクトル.
			{
				if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
				}
				else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				{
					elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				}
			}

			//エレメントの定義を保存.
			inputLayoutDesc.push_back(elementDesc);
		}

		// 入力レイアウトを作成.
		hr = Engine().GetDevice()->CreateInputLayout(
			&inputLayoutDesc[0],	//ステージの入力データ型の配列.
			inputLayoutDesc.size(),		//入力要素の配列内の入力データ型の数.
			pShaderBlob->GetBufferPointer(),	//コンパイル済みシェーダーへのポインタ.
			pShaderBlob->GetBufferSize(),	//コンパイル済み頂点シェーダのサイズ.
			pInputLayout	//作成される入力レイアウトオブジェクトへのポインタ.
		);

		//リフレクション用に確保したメモリを解放.
		pVertexShaderReflection->Release();
		
		return hr;

	}

}