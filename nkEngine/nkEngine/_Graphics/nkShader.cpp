/**
* �V�F�[�_�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkShader.h"

namespace nkEngine
{

	/**
	* �ǂݍ���.
	*
	* @param fileName	�t�@�C����.
	* @param entryName	�G���g���[�|�C���^�ƂȂ�֐��̖��O.
	* @param type		�V�F�[�_�^�C�v.
	*/
	bool Shader::Load(string fileName, const char* entryName, TypeE type)
	{
		Release();
		HRESULT hr = S_OK;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
		//�f�o�b�N���.
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		//�R���p�C���ς݃V�F�[�_�[.
		ScopedResource<ID3DBlob> blobOut;
		//�G���[���b�Z�[�W.
		ScopedResource<ID3DBlob> errorBlob;

		//�V�F�[�_�^�C�v.
		ShaderType_ = type;

		//�V�F�[�_�e�L�X�g.
		static char text[5 * 1024 * 1024];

		//�V�F�[�_�T�C�Y.
		int fileSize = 0;

		string filePath = "Asset/Shader/" + fileName + ".fx";

		//�V�F�[�_�[�����[�h�B
		ReadFile(filePath.c_str(), text, fileSize);

		//�V�F�[�_���f����.
		static const char* shaderModelNames[] = 
		{
			"vs_5_0",
			"ps_5_0",
			"cs_5_0"
		};

		hr = D3DCompile(
			text,	//���R���p�C���̃V�F�[�_�f�[�^�ւ̃|�C���^.
			fileSize,	//�V�F�[�_�f�[�^�̃T�C�Y.
			nullptr,	//(�ȗ��\)�V�F�[�_�t�@�C����.
			nullptr,	//(�ȗ��\)�I�[�}�N����`�̔z��.
			nullptr,	//(�ȗ��\)ID3D10Include�ւ̃|�C���^.(�V�F�[�_�t�@�C���ɃC���N���[�h������Ƃ�����nullptr���Ⴞ��.)
			entryName,	//�G���g���[�֐��̖��O.
			shaderModelNames[(int)ShaderType_],	//�V�F�[�_�@�\�Z�b�g�ł�.
			dwShaderFlags,	//�V�F�[�_�̃R���p�C���I�v�V����.
			0,	//�G�t�F�N�g�̃R���p�C���I�v�V����.
			&blobOut.res,	//�R���p�C�����ꂽ�R�[�h���i�[����ID3D10Blob�̃A�h���X.
			&errorBlob.res	//(�ȗ��\)�R���p�C���̃G���[���b�Z�[�W���i�[����ID3D10Blob�̃A�h���X.
		);
		if (FAILED(hr))
		{
			//�G���[�R�[�h���o��.
			if (errorBlob.res != nullptr) 
			{
				static char errorMessage[10 * 1024];
				sprintf(errorMessage, "filePath : %s, %s", filePath.c_str(), errorBlob.res->GetBufferPointer());
				MessageBox(NULL, errorMessage, "�V�F�[�_�[�R���p�C���G���[", MB_OK);
			}

			return false;
		}

		//�f�o�C�X�̎擾.
		ID3D11Device* Device = Engine().GetDevice();

		//�V�F�[�_�^�C�v���̏���.
		switch (ShaderType_)
		{
		case TypeE::VS:
		{
			//���_�V�F�[�_�[.
			hr = Device->CreateVertexShader(
				blobOut.res->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�ւ̃|�C���^.
				blobOut.res->GetBufferSize(),	//�R���p�C���ςݒ��_�V�F�[�_�̃T�C�Y.
				nullptr,	//�N���X�����N�C���^�[�t�F�C�X�ւ̃|�C���^.
				(ID3D11VertexShader**)&Shader_	//ID3D11VertexShader�C���^�[�t�F�C�X�ւ̃|�C���^.
			);
			if (FAILED(hr)) 
			{
				return false;
			}
			
			//���̓��C�A�E�g���쐬�B
			hr = CreateInputLayout(blobOut.res, &InputLayout_);
			if (FAILED(hr))
			{
				//���̓��C�A�E�g�̍쐬�Ɏ��s����.
				return false;
			}

		}
		break;
		case TypeE::PS:
		{
			//�s�N�Z���V�F�[�_�[.
			hr = Device->CreatePixelShader(
				blobOut.res->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�ւ̃|�C���^.
				blobOut.res->GetBufferSize(),	//�R���p�C���ς݃s�N�Z���V�F�[�_�̃T�C�Y.
				nullptr,	//�N���X�����N�C���^�[�t�F�C�X�ւ̃|�C���^.
				(ID3D11PixelShader**)&Shader_	//ID3D11VertexShader�C���^�[�t�F�C�X�ւ̃|�C���^.
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
	* ���.
	*/
	void Shader::Release()
	{
		if (Shader_ != nullptr) 
		{
			//�V�F�[�_�^�C�v���̉��.
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
			//�C���v�b�g���C�A�E�g�̉��.
			InputLayout_->Release();
			InputLayout_ = nullptr;
		}

	}

	/**
	* �t�@�C���̓ǂݍ���.
	*
	* @param filePath	�t�@�C���p�X.
	* @param readBuffer	�ǂݍ��ݐ�o�b�t�@.
	* @param fileSize	�t�@�C���T�C�Y.
	*/
	void Shader::ReadFile(const char * filePath, char * readBuffer, int & fileSize)
	{
		//�t�@�C���ǂݍ���.
		FILE* fp = fopen(filePath, "rb");
		fseek(fp, 0, SEEK_END);
		fpos_t fPos;
		fgetpos(fp, &fPos);
		fseek(fp, 0, SEEK_SET);
		fileSize = (int)fPos;
		//�o�b�t�@�ɏ�������
		fread(readBuffer, fileSize, 1, fp);
		fclose(fp);
	}

	/**
	* ���_�V�F�[�_�[���璸�_���C�A�E�g�𐶐�.
	*
	* @param pShaderBlob	�R���p�C���ς݃V�F�[�_�ւ̃|�C���^.
	* @param pInputLayout	�C���v�b�g���C�A�E�g�̏o�͐�.
	*/
	HRESULT Shader::CreateInputLayout(ID3DBlob * pShaderBlob, ID3D11InputLayout** pInputLayout)
	{

		HRESULT hr = S_OK;

		//���˃C���^�[�t�F�C�X�ւ̃|�C���^.
		ID3D11ShaderReflection* pVertexShaderReflection;
		
		//�V�F�[�_��񂩂烊�t���N�V�������s��.
		hr = D3DReflect(
			pShaderBlob->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�ւ̃|�C���^.
			pShaderBlob->GetBufferSize(),	//�R���p�C���ςݒ��_�V�F�[�_�̃T�C�Y.
			IID_ID3D11ShaderReflection,	//�g�p����COM�C���^�[�t�F�C�X�̎Q��GUID.
			(void**)&pVertexShaderReflection	//���˃C���^�[�t�F�C�X�ւ̃|�C���^.
		);
		if (FAILED(hr))
		{
			return S_FALSE;
		}

		D3D11_SHADER_DESC shaderDesc;
		pVertexShaderReflection->GetDesc(&shaderDesc);

		//���͏�񃊃X�g.
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

		for (UINT i = 0; i < shaderDesc.InputParameters; i++)
		{
			//�C���v�b�g���.
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

			//�G�������g��`��ݒ�.
			D3D11_INPUT_ELEMENT_DESC elementDesc;
			elementDesc.SemanticName = paramDesc.SemanticName;	//�V�F�[�_�[���͏����ł��̗v�f�Ɋ֘A�t�����Ă���HLSL�Z�}���e�B�N�X.
			elementDesc.SemanticIndex = paramDesc.SemanticIndex;	//�v�f�̃Z�}���e�B�N�X�C���f�b�N�X.(4x4 �̃}�g���N�X�ɂ� 4 �̍\���v�f������A���ꂼ��̍\���v�f�ɂ̓Z�}���e�B�N�X���Ƃ��� matrix ���t�����܂����A4 �̍\���v�f�ɂ͂��ꂼ��قȂ�Z�}���e�B�N�X �C���f�b�N�X (0�A1�A2�A3) �����蓖�Ă��܂�.)
			elementDesc.InputSlot = 0;	//���̓A�Z���u���[�����ʂ��鐮���l.
			elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;	//(�ȗ��\)�e�v�f�Ԃ̃I�t�Z�b�g(�o�C�g�P��).

			//�C���X�^���V���O�p�f�[�^.
			elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;	//�P��̓��̓X���b�g�̓��̓f�[�^�N���X������.
			elementDesc.InstanceDataStepRate = 0;	//�o�b�t�@�[�̒��ŗv�f�� 1 ���i�ޑO�ɁA�C���X�^���X�P�ʂ̓����f�[�^���g�p���ĕ`�悷��C���X�^���X�̐�.

			//�t�H�[�}�b�g�̐ݒ�.

			if (paramDesc.Mask == 1) //1�����x�N�g��.
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
			else if (paramDesc.Mask <= 3) //2�����x�N�g��.
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
			else if (paramDesc.Mask <= 7) //3�����x�N�g��.
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
			else if (paramDesc.Mask <= 15) //4�����x�N�g��.
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

			//�G�������g�̒�`��ۑ�.
			inputLayoutDesc.push_back(elementDesc);
		}

		// ���̓��C�A�E�g���쐬.
		hr = Engine().GetDevice()->CreateInputLayout(
			&inputLayoutDesc[0],	//�X�e�[�W�̓��̓f�[�^�^�̔z��.
			inputLayoutDesc.size(),		//���͗v�f�̔z����̓��̓f�[�^�^�̐�.
			pShaderBlob->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^.
			pShaderBlob->GetBufferSize(),	//�R���p�C���ςݒ��_�V�F�[�_�̃T�C�Y.
			pInputLayout	//�쐬�������̓��C�A�E�g�I�u�W�F�N�g�ւ̃|�C���^.
		);

		//���t���N�V�����p�Ɋm�ۂ��������������.
		pVertexShaderReflection->Release();
		
		return hr;

	}

}