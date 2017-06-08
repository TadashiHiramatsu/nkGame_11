/**
* �u���[�p�V�F�[�_.
*/

/**
* ���_�V�F�[�_�̓��̓��C�A�E�g.
*/
struct VS_INPUT
{
	float4 Pos	: POSITION;		//!< ���W.
	float2 Tex	: TEXCOORD0;	//!< UV���W.
};

/**
* ���_�V�F�[�_�̏o�̓��C�A�E�g.
*/
struct VS_OUTPUT
{
	float4 Pos	: SV_POSITION;	//!< ���W.
	float2 Tex0	: TEXCOORD0;	//!< UV���W0.
	float2 Tex1 : TEXCOORD1;	//!< UV���W1.
	float2 Tex2 : TEXCOORD2;	//!< UV���W2.
};

/** �V���h�E�e�N�X�`��. */
Texture2D SrcTexture : register(t0);
SamplerState SrcSampler : register(s0);

/**
* VS�X�e�[�W�萔�o�b�t�@.
*/
cbuffer VSConstantBuffer : register(b0)
{
	float2 TexSize;	//!< �e�N�X�`���T�C�Y.
}

/**
* X�u���[�p�̒��_�V�F�[�_�[.
*/
VS_OUTPUT VSBlur_X(VS_INPUT In)
{
	VS_OUTPUT Out;

	Out.Pos = In.Pos;

	Out.Tex0 = In.Tex;
	Out.Tex1 = float2(0.5f / TexSize.x, 0.0f);
	Out.Tex2 = float2(1.0f / TexSize.x, 0.0f);

	return Out;
}

/**
* Y�u���[�p�̒��_�V�F�[�_�[.
*/
VS_OUTPUT VSBlur_Y(VS_INPUT In)
{
	VS_OUTPUT Out;

	Out.Pos = In.Pos;

	Out.Tex0 = In.Tex;
	Out.Tex1 = float2(0.0f, 0.5f / TexSize.y);
	Out.Tex2 = float2(0.0f, 1.0f / TexSize.y);

	return Out;
}

/**
* �u���[�p�̃s�N�Z���V�F�[�_�[.
*/
float4 PSBlur(VS_OUTPUT In) : SV_Target
{
	float4 Color = 0;

	//5�_�u���[
	Color = SrcTexture.Sample(SrcSampler, In.Tex0);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 + In.Tex1);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 - In.Tex1);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 + In.Tex2);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 - In.Tex2);
	Color /= 5.0f;

	return Color;
}