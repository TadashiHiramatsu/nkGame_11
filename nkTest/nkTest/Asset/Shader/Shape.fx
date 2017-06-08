/**
* 一般形状描画シェーダ.
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


/** ディフューズライトの数. */
#define NUM_DIFFUSE_LIGHT 6

/** ライト構造体. */
struct LightS
{
	float4 DiffuseLightDir_[NUM_DIFFUSE_LIGHT];		//!< ディフューズライトディレクション.
	float4 DiffuseLightColor_[NUM_DIFFUSE_LIGHT];	//!< ディフューズライトカラー.
	float4 AmbientLight_;							//!< アンビエントライト.
};

/**
* PSステージ定数バッファ.
*/
cbuffer PSConstantBuffer : register(b1)
{
	LightS Light_;	//!< ライト.
}

/**
* ピクセルシェーダのエントリ関数.
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