/**
* FPS�\���E�B���h�E�N���X�̎���.
*/
#include"nkstdafx.h"
#include"nkFPSWindow.h"

namespace nkEngine
{

	namespace
	{
		const int PLOT_SIZE = 50;
	}

	/**
	* ������.
	*/
	void FPSWindow::Start()
	{
		for (int i = 0; i < PLOT_SIZE; i++)
		{
			FPSList_.push_back(0.0f);
		}
	}

	/**
	* �`��.
	*/
	void FPSWindow::Render()
	{
		static int frameCount = 0;
		if (frameCount++ % 10 == 0)
		{
			FPSList_.push_back(Time().GetFPS());
			if (FPSList_.size() > PLOT_SIZE)
			{
				FPSList_.erase(FPSList_.begin());
			}
		}

		ImGui::Begin("FPS");
		ImGui::SetWindowSize(ImVec2(300.0f, 150.0f));
		float FPS = 0.0f;
		if (FPSList_.size() > 0)
		{
			FPS = *(FPSList_.end() - 1);
		}
		ImGui::Text(to_string(FPS).c_str());
		ImGui::PlotLines("FPS�O���t", FPSList_.data(), PLOT_SIZE, 0.0f, nullptr, 0.0f, 120.0f, ImVec2(200.0f, 50.0f));
		ImGui::End();
	}

}