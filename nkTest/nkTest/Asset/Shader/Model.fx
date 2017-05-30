/**
* Model描画シェーダ.
*/

/**
* 頂点シェーダの入力レイアウト.
*/
struct VS_IN
{
	float4 Pos : POSITION0;	//座標.
	float3 Normal : NORMAL;	//法線.
};

/**
* 頂点シェーダの出力レイアウト.
*/
struct VS_OUT
{
	float4 Pos : SV_POSITION;	//座標.
	float3 Normal : TEXCOORD0;	//法線.
	float3 WorldPos : TEXCOORD1;//ワールド座標.
};

/**
* VSステージ定数バッファ.
*/
cbuffer VSConstantBuffer : register(b0)
{
	matrix WorldMatrix_;	//!<ワールド行列.
	matrix ViewMatrix_;		//!<ビュー行列.
	matrix ProjMatrix_;		//!<プロジェクション行列.
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
	matrix LVMatrix; //ライトビュー行列
	matrix LPMatrix; //ライトプロジェクション行列
};

/**
* PSステージ定数バッファ.
*/
cbuffer PSConstantBuffer : register(b0)
{
	LightS Light_;	//!< ライト.
	ShadowReceiverParamS SRP_;	//!< シャドウレシーバー用パラメータ.
	float4 CameraPos_;	//!< カメラの視点.
}

/** シャドウテクスチャ. */
Texture2D ShadowTexture : register(t0);
SamplerState ShadowSampler : register(s0);

/**
* ピクセルシェーダのエントリ関数.
*/
float4 PSMain(VS_OUT In) : SV_Target
{
	float4 Outcolor = float4(0.0f,0.0f,0.0f,1.0f);

	for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
	{
		float4 l = max(0.0f, -dot(In.Normal, Light_.DiffuseLightDir_[i]));
		Outcolor += l * Light_.DiffuseLightColor_[i];
	}

	//ここからスペキュラ.
	//スペキュラカラー.
	float4 SpecColor = 0;

	//頂点から視点へのベクトル.
	float3 toCameraPos = normalize(CameraPos_.xyz - In.WorldPos);

	float3 R = -toCameraPos + 2.0f * dot(In.Normal, toCameraPos) * In.Normal;

	for (int i = 0; i < NUM_DIFFUSE_LIGHT; i++)
	{
		//反射ベクトル.
		float3 L = -Light_.DiffuseLightDir_[i].xyz;

		//スペキュラ強度を計算.
		SpecColor += Light_.DiffuseLightColor_[i] * pow(max(0.0f, dot(L, R)), 2)* Light_.DiffuseLightColor_[i].w;
	}

	Outcolor += SpecColor;

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
		shadow_val = ShadowTexture.Sample(ShadowSampler, shadowMapUV);

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

	Outcolor.xyz *= shadow;

	Outcolor.xyz += Light_.AmbientLight_.xyz;

	return Outcolor;
}