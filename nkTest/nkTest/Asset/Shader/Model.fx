/**
* Model�`��V�F�[�_.
*/

/**
* ���_�V�F�[�_�̓��̓��C�A�E�g.
*/
struct VS_IN
{
	float4 Pos		: POSITION0;	//!< ���W.
	float2 Tex		: TEXCOORD0;	//!< UV���W.
	float3 Normal	: NORMAL;		//!< �@���x�N�g��.
	float3 Tangent	: TANGENT;		//!< �ڃx�N�g��
};

/**
* ���_�V�F�[�_�̏o�̓��C�A�E�g.
*/
struct VS_OUT
{
	float4 Pos		: SV_POSITION;	//!< ���W.
	float2 Tex		: TEXCOORD0;	//!< UV���W.
	float3 Normal	: TEXCOORD1;	//!< �@���x�N�g��.
	float3 Tangent	: TEXCOORD2;	//!< �ڃx�N�g��.
	float3 WorldPos : TEXCOORD3;	//!< ���[���h���W.
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
VS_OUT VSMain(VS_IN In)
{
	VS_OUT Out = (VS_OUT)0;

	float4 pos = In.Pos;

	pos = mul(pos, WorldMatrix_);

	Out.WorldPos = pos.xyz;

	pos = mul(pos, ViewMatrix_);
	pos = mul(pos, ProjMatrix_);

	Out.Pos = pos;

	float3 nor = mul(In.Normal, (float4x3)WorldMatrix_);
	Out.Normal = normalize(nor);
	float3 tan = mul(In.Tangent, (float4x3)WorldMatrix_);
	Out.Tangent = normalize(tan);

	Out.Tex = In.Tex;

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

//�V���h�E���V�[�o�[�p�p�����[�^
struct ShadowReceiverParamS
{
	float4x4 LVMatrix; //���C�g�r���[�s��
	float4x4 LPMatrix; //���C�g�v���W�F�N�V�����s��
};

/**
* PS�X�e�[�W�萔�o�b�t�@.
*/
cbuffer PSConstantBuffer : register(b0)
{
	LightS Light_;	//!< ���C�g.
	ShadowReceiverParamS SRP_;	//!< �V���h�E���V�[�o�[�p�p�����[�^.
	float4 CameraPos_;	//!< �J�����̎��_.
	float4 EffectFlag_;	//!< x:�@���}�b�v, y:�X�y�L�����}�b�v.
}

/** �f�B�t���[�Y�e�N�X�`��. */
Texture2D DiffuseTexture : register(t0);
/** �@���}�b�v. */
Texture2D NormalTexture : register(t1);
/** �X�y�L�����}�b�v. */
Texture2D SpecularTexture : register(t2);
/** �V���h�E�e�N�X�`��. */
Texture2D ShadowTexture : register(t3);

SamplerState Sampler : register(s0);

/**
* �s�N�Z���V�F�[�_�̃G���g���֐�.
*/
float4 PSMain(VS_OUT In) : SV_Target
{
	//�f�B�t���[�Y�F.
	float4 DiffuseColor = DiffuseTexture.Sample(Sampler, In.Tex);

	float3 normal = In.Normal;
	//�@���}�b�v.
	if (EffectFlag_.x > 0.0f)
	{
		normal = NormalTexture.Sample(Sampler, In.Tex);

		//�]�@���x�N�g��.
		float3 biNormal = normalize(cross(In.Tangent, In.Normal));
		normal = (normal * 2.0f) - 1.0f;
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal * normal.z;
	}

	//�A�E�g�v�b�gColor.
	float4 OutColor = DiffuseColor;

	float4 LightColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
	{
		float4 l = max(0.0f, -dot(normal, Light_.DiffuseLightDir_[i]));
		LightColor += l * Light_.DiffuseLightColor_[i];
	}

	//��������X�y�L����.
	if (EffectFlag_.y > 0.0f)
	{
		//�X�y�L�����J���[.
		float4 SpecColor = 0;

		//���_���王�_�ւ̃x�N�g��.
		float3 toCameraPos = normalize(CameraPos_.xyz - In.WorldPos);

		float3 R = -toCameraPos + 2.0f * dot(normal, toCameraPos) * normal;

		for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
		{
			//���˃x�N�g��.
			float3 L = -Light_.DiffuseLightDir_[i].xyz;

			//�X�y�L�������x���v�Z.
			SpecColor += Light_.DiffuseLightColor_[i] * pow(max(0.0f, dot(L, R)), 2)* Light_.DiffuseLightColor_[i].w;
		}

		float4 SpecPower = SpecularTexture.Sample(Sampler, In.Tex);

		LightColor += SpecColor * SpecPower;
	}

	//�e.
	float shadow = 1;

	//���W�v�Z.
	float4 posInLVP = mul(float4(In.WorldPos, 1.0f), SRP_.LVMatrix);
	posInLVP = mul(posInLVP, SRP_.LPMatrix);
	posInLVP.xyz /= posInLVP.w;

	//uv���W�ɕϊ�
	float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
	float2 shadow_val = 1.0f;

	if (shadowMapUV.x < 0.99f && shadowMapUV.y < 0.99f && shadowMapUV.x > 0.01f && shadowMapUV.y > 0.01f)
	{
		shadow_val = ShadowTexture.Sample(Sampler, shadowMapUV);

		float depth = min(posInLVP.z, 1.0f);

		if (depth > shadow_val.r) 
		{
			//�`�F�r�V�F�t
			float depth_sq = shadow_val.r * shadow_val.r;
			float variance = max(shadow_val.g - depth_sq, 0.0006f);
			float md = depth - shadow_val.r;
			float P = variance / (variance + md * md);
			shadow = pow(P, 5.0f);
		}
	}

	LightColor.xyz *= shadow;

	OutColor.xyz *= LightColor.xyz;

	OutColor.xyz += Light_.AmbientLight_.xyz * DiffuseColor.xyz;

	return OutColor;
}