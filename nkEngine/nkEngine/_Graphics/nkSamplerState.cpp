/**
* �T���v���X�e�[�g�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkSamplerState.h"

namespace nkEngine
{

	/**
	* �쐬.
	*/
	bool SamplerState::Create(
		D3D11_TEXTURE_ADDRESS_MODE addressU,
		D3D11_TEXTURE_ADDRESS_MODE addressV
	)
	{

		HRESULT hr;

		// �T���v���[�X�e�[�g�̐ݒ�
		D3D11_SAMPLER_DESC sd;
		ZeroMemory(&sd, sizeof(sd));

		sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	// �t�B���^�����O���\�b�h.
		sd.AddressU = addressU;		// 0 �` 1 �͈̔͊O�ɂ���u���W���������邽�߂Ɏg�p����郁�\�b�h.
		sd.AddressV = addressV;		// 0 �` 1 �͈̔͊O�ɂ���v���W���������邽�߂Ɏg�p����郁�\�b�h.
		sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;	// 0 �` 1 �͈̔͊O�ɂ���w���W���������邽�߂Ɏg�p����郁�\�b�h.
		sd.MipLODBias = 0.0f;	//�v�Z���ꂽ�~�b�v�}�b�v ���x������̃I�t�Z�b�g.
		sd.MaxAnisotropy = 16;	// Filter �� D3D11_FILTER_ANISOTROPIC �܂��� D3D11_FILTER_COMPARISON_ANISOTROPIC ���w�肳��Ă���ꍇ�Ɏg�p�����N�����v�l�ł��B�L���Ȓl�� 1 �` 16 �ł�.
		sd.ComparisonFunc = D3D11_COMPARISON_NEVER;	// �����̃T���v�����O �f�[�^�ɑ΂��ăf�[�^���r����֐�.
		sd.BorderColor[0] = 0.0f;	// AddressU�AAddressV�A�܂��� AddressW �� D3D11_TEXTURE_ADDRESS_BORDER ���w�肳��Ă���ꍇ�Ɏg�p����鋫�E�̐F�ł��B0.0 �` 1.0 �͈̔͂Ŏw�肷��K�v������܂�.
		sd.BorderColor[1] = 0.0f;	// AddressU�AAddressV�A�܂��� AddressW �� D3D11_TEXTURE_ADDRESS_BORDER ���w�肳��Ă���ꍇ�Ɏg�p����鋫�E�̐F�ł��B0.0 �` 1.0 �͈̔͂Ŏw�肷��K�v������܂�.
		sd.BorderColor[2] = 0.0f;	// AddressU�AAddressV�A�܂��� AddressW �� D3D11_TEXTURE_ADDRESS_BORDER ���w�肳��Ă���ꍇ�Ɏg�p����鋫�E�̐F�ł��B0.0 �` 1.0 �͈̔͂Ŏw�肷��K�v������܂�.
		sd.BorderColor[3] = 0.0f;	// AddressU�AAddressV�A�܂��� AddressW �� D3D11_TEXTURE_ADDRESS_BORDER ���w�肳��Ă���ꍇ�Ɏg�p����鋫�E�̐F�ł��B0.0 �` 1.0 �͈̔͂Ŏw�肷��K�v������܂�.
		sd.MinLOD = 0;	// �A�N�Z�X���N�����v����~�b�v�}�b�v�͈͂̉���.
		sd.MaxLOD = FLT_MAX;	// �A�N�Z�X���N�����v����~�b�v�}�b�v�͈͂̏��.

		// �T���v���[�X�e�[�g����
		hr = Engine().GetDevice()->CreateSamplerState(&sd, &D3DSampler_);

		if (FAILED(hr))
		{
			NK_ASSERT(false, "�T���v������");
			return false;
		}

		return true;

	}

}