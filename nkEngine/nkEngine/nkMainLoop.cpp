/**
* メインループクラスの実装.
*/
#include"nkstdafx.h"
#include"nkMainLoop.h"

namespace nkEngine
{

	/**
	* 初期化.
	*/
	bool MainLoop::Init()
	{

		//マルチレンダリングの設定.
		DXGI_SAMPLE_DESC multiSampleDesc;
		multiSampleDesc.Count = 1;
		multiSampleDesc.Quality = 0;

		for (int i = 0; i < 2; i++)
		{
			MainRenderTarget_[i].Create(
				Engine().GetFrameW(),
				Engine().GetFrameH(),
				1,
				DXGI_FORMAT_R8G8B8A8_UNORM,
				DXGI_FORMAT_D24_UNORM_S8_UINT,
				multiSampleDesc
			);
		}

		//レンダリングターゲットビューの設定.
		Engine().GetRenderContext().OMSetRenderTarget(1, &MainRenderTarget_[CurrentMainRenderTarget_]);

		//ビューポートを設定。
		Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, (float)Engine().GetFrameW(), (float)Engine().GetFrameH());

		//シャドウマップの作成.
		ShadowMap_.Create();

		return true;
	}

	/**
	* 更新.
	*/
	void MainLoop::Update()
	{
		Time().Update();

		NK_LOG("FPS:%f\n", Time().GetFPS());

		Input().Update();

		XInput().Update();

		//シーンマネージャの更新.
		SceneManager().Update();

		//初期化されていないオブジェクトを初期化
		GameObjectManager().Start();

		//プリレンダリング前の更新
		GameObjectManager().PreUpdate();

		//更新
		GameObjectManager().Update();

		//Updateの後の更新
		GameObjectManager().PostUpdate();

		//シャドウマップの更新.
		ShadowMap_.Update();

		//削除登録されたGameObjectを削除
		GameObjectManager().Delete();

	}

	/**
	* 描画.
	*/
	void MainLoop::Render()
	{
		//Renderの前の描画
		GameObjectManager().PreRender();

		//シャドウマップの描画.
		ShadowMap_.Render();

		//レンダリングターゲットビューの設定.
		Engine().GetRenderContext().OMSetRenderTarget(1, &MainRenderTarget_[CurrentMainRenderTarget_]);

		//ビューポートを設定。
		Engine().GetRenderContext().RSSetViewport(0.0f, 0.0f, (float)Engine().GetFrameW(), (float)Engine().GetFrameH());

		//レンダリングターゲットビューの0番目をクリア.
		float clearColor[4] = { 0.0f,1.0f,1.0f,1.0f };
		Engine().GetRenderContext().ClearRenderTargetView(0, clearColor);
		Engine().GetRenderContext().ClearDepthStencilView(D3D11_CLEAR_DEPTH);

		//描画
		GameObjectManager().Render();

		//ポストエフェクトの後の描画
		GameObjectManager().PostRender();

		//メインレンダリングターゲットの内容をバックバッファにコピー.
		CopyMainRenderTargetToBackBuffer();

		//バックバッファの内容を画面に描画.
		Engine().GetSwapChain()->Present(0, 0);

	}

	/**
	* 解放.
	*/
	void MainLoop::Release()
	{
		//メインレンダリングターゲットの解放.
		for (int i = 0; i < 2; i++)
		{
			MainRenderTarget_[i].Release();
		}
	}

	/**
	* メインレンダリングターゲットの内容をバックバッファにコピー.
	*/
	void MainLoop::CopyMainRenderTargetToBackBuffer()
	{
		//バックバッファ.
		ID3D11Texture2D* D3DBackBuffer = NULL;
		//バックバッファを取得.
		Engine().GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&D3DBackBuffer);

		//メインレンダリングターゲットをバックバッファにコピー.
		Engine().GetRenderContext().CopyResource(D3DBackBuffer,MainRenderTarget_[CurrentMainRenderTarget_].GetRenderTarget());
	
		//バックバッファを解放.
		D3DBackBuffer->Release();
	
	}

}