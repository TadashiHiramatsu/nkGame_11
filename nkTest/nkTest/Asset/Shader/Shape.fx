/**
* ��ʌ`��`��V�F�[�_.
*/

/**
* ���_�V�F�[�_�̓��̓��C�A�E�g.
*/
struct VS_IN
{
	float4 Pos : POSITION0;	//���W.
	float3 Normal : NORMAL;	//�@��.
};

/**
* ���_�V�F�[�_�̏o�̓��C�A�E�g.
*/
struct VS_OUT
{
	float4 Pos : SV_POSITION;	//���W.
	float3 Normal : TEXCOORD0;	//�@��.
};


/**
* VS�X�e�[�W�萔�o�b�t�@.
*/
cbuffer VSConstantBuffer : register(b0)
{
	float4x4 WorldMatrix_;	//!<���[���h�s��.
	float4x4 ViewMatrix_;		//!<�r���[�s��.
	float4x4 ProjMatrix_;		//!<�v���W�F�N�V�����s��.
}

/**
* ���_�V�F�[�_�̃G���g���֐�.
*/
VS_OUT VSShape(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	float4 pos = In.Pos;

	pos = mul(pos, WorldMatrix_);
	pos = mul(pos, ViewMatrix_);
	pos = mul(pos, ProjMatrix_);

	Out.Pos = pos;
	float3 nor = mul(In.Normal, (float3x3)WorldMatrix_);
	Out.Normal = normalize(nor);

	return Out;
}


/** �f�B�t���[�Y���C�g�̐�. */
#define NUM_DIFFUSE_LIGHT 6

/** ���C�g�\����. */
struct LightS
{
	float4 DiffuseLightDir_[NUM_DIFFUSE_LIGHT];		//!< �f�B�t���[�Y���C�g�f�B���N�V����.
	float4 DiffuseLightColor_[NUM_DIFFUSE_LIGHT];	//!< �f�B�t���[�Y���C�g�J���[.
	float4 AmbientLight_;							//!< �A���r�G���g���C�g.
};

/**
* PS�X�e�[�W�萔�o�b�t�@.
*/
cbuffer PSConstantBuffer : register(b1)
{
	LightS Light_;	//!< ���C�g.
}

/**
* �s�N�Z���V�F�[�_�̃G���g���֐�.
*/
float4 PSShape(VS_OUT In) : SV_Target
{
	float4 color = float4(0.0f,0.0f,0.0f,1.0f);

	for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
	{
		float4 l = max(0.0f, -dot(In.Normal, Light_.DiffuseLightDir_[i]));
		color += l * Light_.DiffuseLightColor_[i];
	}

	return color;
}