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
		ImGui::Begin("GameObjectWindow");
		ImGui::SetWindowSize(ImVec2(500.0f, 300.0f), ImGuiSetCond_FirstUseEver);

		ImGui::BeginChild("List", ImVec2(150, 0), true);

		static int selected = 0;

		auto& goList = GameObjectManager().GetGameObjectList();
		static IGameObject* selectObject = nullptr;
		for (auto& objList : goList)
		{
			for (auto obj : objList)
			{
				ImGui::Bullet();
				if (ImGui::Selectable(obj->GetName().c_str(), obj == selectObject))
				{
					selectObject = obj;
				}
			}
		}

		ImGui::EndChild();
		ImGui::SameLine();

		ImGui::BeginGroup();
		
		if (selectObject != nullptr)
		{
			//ゲームオブジェクト名表示.
			ImGui::BulletText(selectObject->GetName().c_str());

			//コンポーネント名表示.
			ImGui::Text("Transform");

			const float MOVE_SPEED = 0.05f;

			//座標表示.
			ImGui::DragFloat3("Position", selectObject->Transform_.Position_.v, MOVE_SPEED);
			//回転表示.
			Vector3 rot = selectObject->Transform_.Rotation_.GetEuler();
			ImGui::DragFloat3("Rotation", rot.v, MOVE_SPEED);
			selectObject->Transform_.Rotation_.RotationEuler(rot);
			//拡大表示.
			ImGui::DragFloat3("Scale", selectObject->Transform_.Scale_.v, MOVE_SPEED);

		}

		ImGui::EndGroup();

		ImGui::End();

		//ImGui::ShowTestWindow();
	}

}