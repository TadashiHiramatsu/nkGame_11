/**
* FPS表示ウィンドウクラスの実装.
*/
#include"nkstdafx.h"
#include"nkFPSWindow.h"

#include <iomanip>

namespace nkEngine
{

	namespace
	{
		const int PLOT_SIZE = 50;
	}

	/**
	* 初期化.
	*/
	void FPSWindow::Start()
	{
		for (int i = 0; i < PLOT_SIZE; i++)
		{
			FPSList_.push_back(60.0f);
		}
	}

	/**
	* 描画.
	*/
	void FPSWindow::Render()
	{
		const float MeasurementTime = 0.3f;
		static float LocalTime = 0.0f;
		LocalTime += Time().DeltaTime();
		if (LocalTime >= MeasurementTime)
		{
			FPSList_.push_back(Time().GetFPS());
			if (FPSList_.size() > PLOT_SIZE)
			{
				FPSList_.erase(FPSList_.begin());
			}
			LocalTime = 0.0f;
		}

		ImGui::Begin("FPSWindow");
		ImGui::SetWindowSize(ImVec2(300.0f, 150.0f));
		float FPS = 0.0f;
		FPS = *(FPSList_.end() - 1);
		ImGui::Text(to_string(FPS).c_str());
		ImGui::PlotLines("FPSグラフ", FPSList_.data(), PLOT_SIZE, 0.0f, nullptr, 0.0f, 120.0f, ImVec2(200.0f, 50.0f));
		ImGui::End();
	}

}