/**
* ゲームオブジェクト表示ウィンドウクラスの実装.
*/
#include"nkstdafx.h"
#include"nkGameObjectWindow.h"

namespace nkEngine
{

	/**
	* 描画.
	*/
	void GameObjectWindow::Render()
	{
		ImGui::Begin("GameObject");
		ImGui::SetWindowSize(ImVec2(500.0f, 300.0f), ImGuiSetCond_FirstUseEver);

		auto& goList = GameObjectManager().GetGameObjectList();

		for (auto& objList : goList)
		{
			for (auto obj : objList)
			{
				ImGui::Text(obj->GetName().c_str());
			}
		}

		ImGui::End();
	}

}