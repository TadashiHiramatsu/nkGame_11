/**
* Model描画シェーダ.
*/

/**
* 頂点シェーダの入力レイアウト.
*/
struct VS_IN
{
	float4 Pos		: POSITION0;	//!< 座標.
	float2 Tex		: TEXCOORD0;	//!< UV座標.
	float3 Normal	: NORMAL;		//!< 法線ベクトル.
	float3 Tangent	: TANGENT;		//!< 接ベクトル
};

/**
* 頂点シェーダの出力レイアウト.
*/
struct VS_OUT
{
	float4 Pos		: SV_POSITION;	//!< 座標.
	float2 Tex		: TEXCOORD0;	//!< UV座標.
	float3 Normal	: TEXCOORD1;	//!< 法線ベクトル.
	float3 Tangent	: TEXCOORD2;	//!< 接ベクトル.
	float3 WorldPos : TEXCOORD3;	//!< ワールド座標.
};

/**
* VSステージ定数バッファ.
*/
cbuffer VSConstantBuffer : register(b0)
{
	float4x4 WorldMatrix_;	//!<ワールド行列.
	float4x4 ViewMatrix_;		//!<ビュー行列.
	float4x4 ProjMatrix_;		//!<プロジェクション行列.
}

/**
* 頂点シェーダのエントリ関数.
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

/** ディフューズライトの数. */
#define NUM_DIFFUSE_LIGHT 6

/** ライト構造体. */
struct LightS
{
	float4 DiffuseLightDir_[NUM_DIFFUSE_LIGHT];		//!< ディフューズライトディレクション.
	float4 DiffuseLightColor_[NUM_DIFFUSE_LIGHT];	//!< ディフューズライトカラー.
	float4 AmbientLight_;							//!< アンビエントライト.
};

//シャドウレシーバー用パラメータ
struct ShadowReceiverParamS
{
	float4x4 LVMatrix; //ライトビュー行列
	float4x4 LPMatrix; //ライトプロジェクション行列
};

/**
* PSステージ定数バッファ.
*/
cbuffer PSConstantBuffer : register(b0)
{
	LightS Light_;	//!< ライト.
	ShadowReceiverParamS SRP_;	//!< シャドウレシーバー用パラメータ.
	float4 CameraPos_;	//!< カメラの視点.
	float4 EffectFlag_;	//!< x:法線マップ, y:スペキュラマップ.
}

/** ディフューズテクスチャ. */
Texture2D DiffuseTexture : register(t0);
/** 法線マップ. */
Texture2D NormalTexture : register(t1);
/** スペキュラマップ. */
Texture2D SpecularTexture : register(t2);
/** シャドウテクスチャ. */
Texture2D ShadowTexture : register(t3);

SamplerState Sampler : register(s0);

/**
* ピクセルシェーダのエントリ関数.
*/
float4 PSMain(VS_OUT In) : SV_Target
{
	//ディフューズ色.
	float4 DiffuseColor = DiffuseTexture.Sample(Sampler, In.Tex);

	float3 normal = In.Normal;
	//法線マップ.
	if (EffectFlag_.x > 0.0f)
	{
		normal = NormalTexture.Sample(Sampler, In.Tex);

		//従法線ベクトル.
		float3 biNormal = normalize(cross(In.Tangent, In.Normal));
		normal = (normal * 2.0f) - 1.0f;
		normal = In.Tangent * normal.x + biNormal * normal.y + In.Normal * normal.z;
	}

	//アウトプットColor.
	float4 OutColor = DiffuseColor;

	float4 LightColor = float4(0.0f, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
	{
		float4 l = max(0.0f, -dot(normal, Light_.DiffuseLightDir_[i]));
		LightColor += l * Light_.DiffuseLightColor_[i];
	}

	//ここからスペキュラ.
	if (EffectFlag_.y > 0.0f)
	{
		//スペキュラカラー.
		float4 SpecColor = 0;

		//頂点から視点へのベクトル.
		float3 toCameraPos = normalize(CameraPos_.xyz - In.WorldPos);

		float3 R = -toCameraPos + 2.0f * dot(normal, toCameraPos) * normal;

		for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
		{
			//反射ベクトル.
			float3 L = -Light_.DiffuseLightDir_[i].xyz;

			//スペキュラ強度を計算.
			SpecColor += Light_.DiffuseLightColor_[i] * pow(max(0.0f, dot(L, R)), 2)* Light_.DiffuseLightColor_[i].w;
		}

		float4 SpecPower = SpecularTexture.Sample(Sampler, In.Tex);

		LightColor += SpecColor * SpecPower;
	}

	//影.
	float shadow = 1;

	//座標計算.
	float4 posInLVP = mul(float4(In.WorldPos, 1.0f), SRP_.LVMatrix);
	posInLVP = mul(posInLVP, SRP_.LPMatrix);
	posInLVP.xyz /= posInLVP.w;

	//uv座標に変換
	float2 shadowMapUV = float2(0.5f, -0.5f) * posInLVP.xy + float2(0.5f, 0.5f);
	float2 shadow_val = 1.0f;

	if (shadowMapUV.x < 0.99f && shadowMapUV.y < 0.99f && shadowMapUV.x > 0.01f && shadowMapUV.y > 0.01f)
	{
		shadow_val = ShadowTexture.Sample(Sampler, shadowMapUV);

		float depth = min(posInLVP.z, 1.0f);

		if (depth > shadow_val.r) 
		{
			//チェビシェフ
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