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
	virtual void onCreate() override
	{
		INF.init();

		INF.pushNode<DummyNode>();
		INF.pushNode<DummyNode>();
		INF.pushNode<SumNode>();
		INF.pushNode<MultiplyNode>();
		INF.pushNode<ReadNode>();
	}

	virtual void onDestroy() override
	{
		INF.destroy();
	}
    
	virtual void update();

	virtual void menuBar() override
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
