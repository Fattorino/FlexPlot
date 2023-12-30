#pragma once

#include <imgui.h>
#include <vector>
#include <implot.h>

#include "includes/ToroImGuiHandle/ToroImGuiHandle.h"
#include "nodes.h"

#define SUM_VEC(a, b) ImVec2(a.x + b.x, a.y + b.y)

class FlexPlot : public appLayer
{
private:
	float m_wsplit = 200.f;
	int m_dragging = 0;

	void m_nodesBar();

public:
	void onCreate() override
	{
		INF.init();

		INF.pushNode<CsvColumnReader>();
		INF.pushNode<SumNode>();
		INF.pushNode<MultiplyNode>();
		INF.pushNode<ReadNode>();
	}

	void onDestroy() override
	{
		INF.destroy();
	}
    
	void update() override;

	void menuBar() override
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Dummy"))
			{
			}
			ImGui::EndMenu();
		}
	}
};
