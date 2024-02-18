#include "FlexPlot.h"

void FlexPlot::m_nodesBar()
{
	ImGui::Text("NodesBar");
	ImGui::Separator();

	ImGui::Button("SUM");
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) { m_dragging = 1; }
	
	ImGui::Button("SUBTRACT");
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) { m_dragging = 2; }

	ImGui::Button("MULTIPLY");
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) { m_dragging = 3; }

	ImGui::Button("DIVIDE");
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) { m_dragging = 4; }

	if (m_dragging > 0 && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
	{
		switch (m_dragging)
		{
		case 1:
            //ImNodeFlow::pushNode<SumNode>(ImGui::GetMousePos(), true);
			m_dragging = 0;
			break;
		case 2:
            //ImNodeFlow::pushNode<SubtractNode>(ImGui::GetMousePos(), true);
			m_dragging = 0;
			break;
		case 3:
            //ImNodeFlow::pushNode<MultiplyNode>(ImGui::GetMousePos(), true);
			m_dragging = 0;
			break;
		case 4:
            //ImNodeFlow::pushNode<DivideNode>(ImGui::GetMousePos(), true);
			m_dragging = 0;
			break;
		default:
			break;
		}
	}
}

void FlexPlot::update()
{
	ImGui::SetNextWindowSize(ImVec2(800, 500), ImGuiCond_Appearing);
	ImGui::Begin("FlexPlot Flow");

	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.f);
	ImGui::BeginChild("NodesBar", ImVec2(m_split, 0), true);
	ImGui::PopStyleVar();
	m_nodesBar();
	ImGui::EndChild();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::SameLine();
	ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, ImGui::GetContentRegionAvail().y));
	if (ImGui::IsItemActive())
        m_split += ImGui::GetIO().MouseDelta.x;
	ImGui::SameLine();
	ImGui::PopStyleVar();

    inf.update();

	if (m_dragging > 0)
	{
		ImGui::SetNextWindowPos(ImGui::GetMousePos());
		ImGui::BeginChild("DummyBABA", ImVec2(50, 50), true);
		ImGui::EndChild();
	}

	ImGui::End();
}
