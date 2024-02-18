#pragma once

#include <imgui.h>
#include <vector>
#include <implot.h>

#include <ImGuiHandler.h>
#include <ImNodeFlow.h>
#include "nodes.h"

using namespace ImFlow;

class FlexPlot : public appLayer
{
public:
    void onCreate() override
    {
        inf.addNode<CsvReader>({0, 0});
    }

    void update() override;

private:
    ImNodeFlow inf;
	float m_split = 200.f;
	int m_dragging = 0;

	void m_nodesBar();
};
