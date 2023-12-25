#include "FlexPlot.h"

void FlexPlot::m_nodesBar()
{
	ImGui::Text("NodesBar");
	ImGui::Separator();

	if (ImGui::Button("SUM"));
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		m_dragging = 1;
	}
	
	ImGui::Button("SUBTRACT");
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		m_dragging = 2;
	}

	ImGui::Button("MULTIPLY");
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		m_dragging = 3;
	}

	ImGui::Button("DIVIDE");
	if (ImGui::IsItemHovered() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
	{
		m_dragging = 4;
	}

	// ImGui::Text("%.2f %.2f", ImGui::GetMousePos().x, ImGui::GetMousePos().y);

	if (m_dragging > 0 && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
	{
		switch (m_dragging)
		{
		case 1:
			INF.pushNode<SumNode>(ImGui::GetMousePos(), true);
			m_dragging = 0;
			break;
		case 2:
			INF.pushNode<SubtractNode>(ImGui::GetMousePos(), true);
			m_dragging = 0;
			break;
		case 3:
			INF.pushNode<MultiplyNode>(ImGui::GetMousePos(), true);
			m_dragging = 0;
			break;
		case 4:
			INF.pushNode<DivideNode>(ImGui::GetMousePos(), true);
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
	ImGui::BeginChild("NodesBar", ImVec2(m_wsplit, 0), true);
	ImGui::PopStyleVar();
	m_nodesBar();
	ImGui::EndChild();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	ImGui::SameLine();
	ImGui::InvisibleButton("vsplitter", ImVec2(8.0f, ImGui::GetContentRegionAvail().y));
	if (ImGui::IsItemActive())
		m_wsplit += ImGui::GetIO().MouseDelta.x;
	ImGui::SameLine();
	ImGui::PopStyleVar();

	ImGui::BeginChild("FlowGrid", ImVec2(0, 0));
	INF.update();
	ImGui::EndChild();

	if (m_dragging > 0)
	{
		ImGui::SetNextWindowPos(ImGui::GetMousePos());
		ImGui::BeginChild("DummyBABA", ImVec2(50, 50), true);
		ImGui::EndChild();
	}

	ImGui::End();
}
