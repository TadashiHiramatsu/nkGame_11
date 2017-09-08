/**
* �Q�[���I�u�W�F�N�g�\���E�B���h�E�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkGameObjectWindow.h"

namespace nkEngine
{

	/**
	* �`��.
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
			//�Q�[���I�u�W�F�N�g���\��.
			ImGui::BulletText(selectObject->GetName().c_str());

			//�R���|�[�l���g���\��.
			ImGui::Text("Transform");

			const float MOVE_SPEED = 0.05f;

			//���W�\��.
			ImGui::DragFloat3("Position", selectObject->Transform_.Position_.v, MOVE_SPEED);
			//��]�\��.
			Vector3 rot = selectObject->Transform_.Rotation_.GetEuler();
			ImGui::DragFloat3("Rotation", rot.v, MOVE_SPEED);
			selectObject->Transform_.Rotation_.RotationEuler(rot);
			//�g��\��.
			ImGui::DragFloat3("Scale", selectObject->Transform_.Scale_.v, MOVE_SPEED);

		}

		ImGui::EndGroup();

		ImGui::End();

		//ImGui::ShowTestWindow();
	}

}