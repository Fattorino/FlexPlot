#include "nodes.h"

void CsvColumnReader::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));
	ImGui::Text("CSV Column reader");

	// ImGui::SetNextItemWidth(70.f);
	ImGui::InputTextWithHint("##InputCsvPath", "Fil path (.csv)", &m_filepath);
    if(ImGui::Button("Load"))
    {
        m_doc.Load(m_filepath);
        // m_columnsName.clear();
        m_columnsName = m_doc.GetColumnNames();
    }

    ImToro::vCombo("Column", &m_selectedCol, m_columnsName);

    if(ImGui::Button("Refresh"))
    {
        m_data = m_doc.GetColumn<float>(m_selectedCol);
    }

	// ImGui::SameLine();
	out.render();

	ImNode::EndNode();
}

std::vector<float> CsvColumnReader::getOut(int index)
{
	return m_data;
}

// ---------------------------------------------------------------------------------------------------------------------

void SumNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));

	inA.render();
	ImGui::Text("    +  ");
	ImGui::SameLine();
	out.render();
	inB.render();

	ImNode::EndNode();
}

std::vector<float> SumNode::getOut(int index)
{
    m_data.clear();
    for (int i = 0; i < inA.getLink()->fromPin->getParent()->getOut(0).size() && i < inB.getLink()->fromPin->getParent()->getOut(0).size(); ++i)
    {
        float a = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOut(0)[i] : 0.0f;
        float b = (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOut(0)[i] : 0.0f;
        m_data.emplace_back(a + b);
    }

    return m_data;
}

// ---------------------------------------------------------------------------------------------------------------------

void MultiplyNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));

	inA.render();
	ImGui::Text("    *  ");
	ImGui::SameLine();
	out.render();
	inB.render();

	ImNode::EndNode();
}

std::vector<float> MultiplyNode::getOut(int index)
{
    m_data.clear();
    for (int i = 0; i < inA.getLink()->fromPin->getParent()->getOut(0).size() && i < inB.getLink()->fromPin->getParent()->getOut(0).size(); ++i)
    {
        float a = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOut(0)[i] : 1.0f;
        float b = (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOut(0)[i] : 1.0f;
        m_data.emplace_back(a * b);
    }

    return m_data;
}

// ---------------------------------------------------------------------------------------------------------------------

void SubtractNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));

	inA.render();
	ImGui::Text("    -  ");
	ImGui::SameLine();
	out.render();
	inB.render();

	ImNode::EndNode();
}

std::vector<float> SubtractNode::getOut(int index)
{
    m_data.clear();
    for (int i = 0; i < inA.getLink()->fromPin->getParent()->getOut(0).size() && i < inB.getLink()->fromPin->getParent()->getOut(0).size(); ++i)
    {
        float a = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOut(0)[i] : 0.0f;
        float b = (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOut(0)[i] : 0.0f;
        m_data.emplace_back(a - b);
    }

    return m_data;
}

// ---------------------------------------------------------------------------------------------------------------------

void DivideNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));

	inA.render();
	ImGui::Text("    /  ");
	ImGui::SameLine();
	out.render();
	inB.render();

	ImNode::EndNode();
}

std::vector<float> DivideNode::getOut(int index)
{
    m_data.clear();
    for (int i = 0; i < inA.getLink()->fromPin->getParent()->getOut(0).size() && i < inB.getLink()->fromPin->getParent()->getOut(0).size(); ++i)
    {
        float a = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOut(0)[i] : 1.0f;
        float b = (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOut(0)[i] : 1.0f;
        m_data.emplace_back(a / b);
    }

    return m_data;
}

// ---------------------------------------------------------------------------------------------------------------------

void ReadNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));
	ImGui::Text("IN VAL:");

	inA.render();
	//ImGui::SameLine();
	//ImGui::Text("%f", val);

	ImNode::EndNode();
}

void ReadNode::resolveChain()
{
    m_data = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOut(0) : std::vector<float>();
}
