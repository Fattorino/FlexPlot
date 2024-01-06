#pragma once

#include <imgui.h>
#include <vector>
#include <implot.h>

#include "ToroImGuiHandle.hpp"
#include "nodes.h"

#define SUM_VEC(a, b) ImVec2(a.x + b.x, a.y + b.y)

class FlexPlot : public appLayer
{
private:
	float m_split = 200.f;
	int m_dragging = 0;

    std::vector<std::shared_ptr<BaseNode>> m_nodes;

	void m_nodesBar();

public:
	void onCreate() override
	{
        ImNodeFlow::init(m_nodes);

        ImNodeFlow::pushNode<CsvColumnReader>();
        ImNodeFlow::pushNode<SumNode>();
        ImNodeFlow::pushNode<MultiplyNode>();
        ImNodeFlow::pushNode<ReadNode>();
	}

    ~FlexPlot() { ImNodeFlow::destroy(); }
    
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
