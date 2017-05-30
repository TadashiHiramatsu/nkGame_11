/**
* レンダリングコンテキストクラスの実装.
*/
#include"nkstdafx.h"
#include"nkRenderContext.h"

namespace nkEngine
{

	/**
	* 初期化.
	*
	* @param d3dDeviceContext	D3Dデバイスコンテキスト.
	*/
	void RenderContext::Init(ID3D11DeviceContext * d3dDeviceContext)
	{
		//デバイスコンテキストの設定.
		D3DDeviceContext_ = d3dDeviceContext;
	}

	/**
	* レンダリングターゲットビューと深度ステンシルビューを設定.
	* 深度ステンシルビューは一つのものが適応される.
	*
	* @param numView			登録するレンダリングターゲットクラスの数.
	* @param renderTarget		登録するレンダリングターゲットクラス.
	*/
	void RenderContext::OMSetRenderTarget(UINT numView, RenderTarget* renderTarget)
	{
		//レンダリングターゲットビューと深度ステンシルビューの設定.
		ZeroMemory(RenderTargetViewList_, sizeof(RenderTargetViewList_));
		DepthStencilView_ = renderTarget[0].GetDepthStencilView();
		for (UINT i = 0; i < numView; i++)
		{
			RenderTargetViewList_[i] = renderTarget[0].GetRenderTargetView();
		}
		D3DDeviceContext_->OMSetRenderTargets(numView, RenderTargetViewList_, DepthStencilView_);
		NumRenderTargetView_ = numView;
	}

}