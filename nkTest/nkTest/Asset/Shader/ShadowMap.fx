/**
* シャドウマップ書き込み描画シェーダ.
*/

/**
* 頂点シェーダの入力レイアウト.
*/
struct VS_INPUT
{
	float4 Pos		: POSITION;	//座標.
	float3 Normal	: NORMAL;	//法線.
};

//シャドウマップ出力頂点
struct VS_OUTPUT
{
	float4 Pos		: SV_POSITION;	//座標.
	float4 Depth	: TEXCOORD0;	//深度.
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
* シャドウマップ書き込み用頂点シェーダー.
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
* シャドウマップ書き込み用ピクセルシェーダー.
*/
float4 PSShadowMap(VS_OUTPUT In) : SV_Target
{
	//深度計算.
	float z = In.Depth.z / In.Depth.w;
	float dx = ddx(z);
	float dy = ddy(z);
	return float4(z, z*z + 0.25f * (dx*dx + dy*dy), 0.0f, 1.0f);
}