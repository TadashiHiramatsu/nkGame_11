/**
* ブラー用シェーダ.
*/

/**
* 頂点シェーダの入力レイアウト.
*/
struct VS_INPUT
{
	float4 Pos	: POSITION;		//!< 座標.
	float2 Tex	: TEXCOORD0;	//!< UV座標.
};

/**
* 頂点シェーダの出力レイアウト.
*/
struct VS_OUTPUT
{
	float4 Pos	: SV_POSITION;	//!< 座標.
	float2 Tex0	: TEXCOORD0;	//!< UV座標0.
	float2 Tex1 : TEXCOORD1;	//!< UV座標1.
	float2 Tex2 : TEXCOORD2;	//!< UV座標2.
};

/** シャドウテクスチャ. */
Texture2D SrcTexture : register(t0);
SamplerState SrcSampler : register(s0);

/**
* VSステージ定数バッファ.
*/
cbuffer VSConstantBuffer : register(b0)
{
	float2 TexSize;	//!< テクスチャサイズ.
}

/**
* Xブラー用の頂点シェーダー.
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
* Yブラー用の頂点シェーダー.
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
* ブラー用のピクセルシェーダー.
*/
float4 PSBlur(VS_OUTPUT In) : SV_Target
{
	float4 Color = 0;

	//5点ブラー
	Color = SrcTexture.Sample(SrcSampler, In.Tex0);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 + In.Tex1);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 - In.Tex1);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 + In.Tex2);
	Color += SrcTexture.Sample(SrcSampler, In.Tex0 - In.Tex2);
	Color /= 5.0f;

	return Color;
}