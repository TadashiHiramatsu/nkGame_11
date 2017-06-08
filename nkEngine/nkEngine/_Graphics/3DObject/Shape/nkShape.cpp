/**
* 形状の基底クラスの実装.
*/
#include"nkstdafx.h"
#include"nkShape.h"

namespace nkEngine
{

	/**
	* 作成.
	*
	* @param transform	トランスフォームのポインタ.
	* @param light		ライトのポインタ.
	* @param camera		カメラのポインタ.
	*/
	void IShape::Create(Transform * transform, Light * light, Camera * camera)
	{
		Transform_ = transform;
		Light_ = light;
		Camera_ = camera;

		//頂点シェーダーをロード。
		VShader_.Load("Shape", "VSShape", Shader::TypeE::VS);
		//ピクセルシェーダーをロード。
		PShader_.Load("Shape", "PSShape", Shader::TypeE::PS);

		CreateBuffer();

	}

	/**
	* 描画.
	*/
	void IShape::Render()
	{

		//頂点バッファを設定.
		Engine().GetRenderContext().IASetVertexBuffer(VertexBuffer_);
		//インデックスバッファを設定.
		Engine().GetRenderContext().IASetIndexBuffer(IndexBuffer_, DXGI_FORMAT_R16_UINT);

		//プリミティブのトポロジーを設定.
		Engine().GetRenderContext().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//頂点シェーダーを設定.
		Engine().GetRenderContext().VSSetShader(VShader_);
		//ピクセルシェーダーを設定.
		Engine().GetRenderContext().PSSetShader(PShader_);
		//入力レイアウトを設定.
		Engine().GetRenderContext().IASetInputLayout(VShader_.GetInputLayout());

		VSConstantBufferS vsConstant;
		vsConstant.WorldMatrix_ = Transform_->WorldMatrix_;
		vsConstant.ViewMatrix_ = Camera_->GetViewMatrix();
		vsConstant.ProjMatrix_ = Camera_->GetProjectionMatrix();
		//VSステージの定数バッファを更新.
		Engine().GetRenderContext().UpdateSubresource(VSConstantBuffer_, vsConstant);
		//VSステージの定数バッファを設定.
		Engine().GetRenderContext().VSSetConstantBuffer(0, VSConstantBuffer_);

		PSConstantBufferS psConstant;
		psConstant.Light_ = *Light_;
		//VSステージの定数バッファを更新.
		Engine().GetRenderContext().UpdateSubresource(PSConstantBuffer_, psConstant);
		//VSステージの定数バッファを設定.
		Engine().GetRenderContext().PSSetConstantBuffer(1, PSConstantBuffer_);

		//描画。
		Engine().GetRenderContext().DrawIndexed(36, 0, 0);

	}

	/**
	* バッファの作成.
	*/
	void IShape::CreateBuffer()
	{
		//VSステージの定数バッファを作成.
		VSConstantBuffer_.Create(nullptr, sizeof(VSConstantBufferS));
		//PSステージの定数バッファを作成.
		PSConstantBuffer_.Create(nullptr, sizeof(PSConstantBufferS));
	}

}