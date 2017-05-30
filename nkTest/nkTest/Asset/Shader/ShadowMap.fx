/**
* �V���h�E�}�b�v�������ݕ`��V�F�[�_.
*/

/**
* ���_�V�F�[�_�̓��̓��C�A�E�g.
*/
struct VS_INPUT
{
	float4 Pos		: POSITION;	//���W.
	float3 Normal	: NORMAL;	//�@��.
};

//�V���h�E�}�b�v�o�͒��_
struct VS_OUTPUT
{
	float4 Pos		: SV_POSITION;	//���W.
	float4 Depth	: TEXCOORD0;	//�[�x.
};

/**
* VS�X�e�[�W�萔�o�b�t�@.
*/
cbuffer VSConstantBuffer : register(b0)
{
	matrix WorldMatrix_;	//!<���[���h�s��.
	matrix ViewMatrix_;		//!<�r���[�s��.
	matrix ProjMatrix_;		//!<�v���W�F�N�V�����s��.
}

/**
* �V���h�E�}�b�v�������ݗp���_�V�F�[�_�[.
*/
VS_OUTPUT VSShadowMap(VS_INPUT In)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;
	
	float4 pos = In.Pos;
	pos = mul(pos, WorldMatrix_);
	pos = mul(pos, ViewMatrix_);
	pos = mul(pos, ProjMatrix_);

	Out.Depth = Out.Pos = pos;

	return Out;
}

/**
* �V���h�E�}�b�v�������ݗp�s�N�Z���V�F�[�_�[.
*/
float4 PSShadowMap(VS_OUTPUT In) : SV_Target
{
	//�[�x�v�Z.
	float z = In.Depth.z / In.Depth.w;
	float dx = ddx(z);
	float dy = ddy(z);
	return float4(z, z*z + 0.25f * (dx*dx + dy*dy), 0.0f, 1.0f);
}