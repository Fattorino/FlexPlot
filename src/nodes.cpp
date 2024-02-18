#include "nodes.h"

void CsvColumnReader::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));
	ImGui::Text("CSV Column reader");
    ImGui::Spacing();

	ImGui::SetNextItemWidth(150.f);
	ImGui::InputTextWithHint("##InputCsvPath", "Fil path (.csv)", &m_filepath);
    ImGui::SameLine();
    if(ImGui::Button("Search"))
    {
        nfdchar_t* outPath;
        nfdfilteritem_t filterItem[1] = { { "CSV file", "csv,txt" }};
        nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, nullptr);

        NFD_Init();

        if (result == NFD_OKAY)
        {
            m_filepath.assign(outPath);
            NFD_FreePath(outPath);
        }
        else if (result == NFD_CANCEL) { puts("User pressed cancel."); }
        else { printf("Error: %s\n", NFD_GetError()); }

        NFD_Quit();
    }
    if(ImGui::Button("Load"))
    {
        m_doc.Load(m_filepath);
        m_columnsName = m_doc.GetColumnNames();
    }

    ImGui::SetNextItemWidth(150.f);
    ImGui::BeginGroup();
    ImToro::vCombo("Column", &m_selectedCol, m_columnsName);
    ImGui::EndGroup();

    if(ImGui::Button("Refresh"))
    {
        m_data = m_doc.GetColumn<float>(m_selectedCol);
    }

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

void ReadNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));
	ImGui::Text("IN VAL:");

	inA.render();

	ImNode::EndNode();

    //ImNode::Suspend();
    ImGui::BeginChild("List", ImVec2(170, 200));
    for (auto& l : m_data)
    {
        ImGui::Text("Val: %f", l);
    }
    ImGui::EndChild();
    //ImNode::Resume();
}

void ReadNode::resolveChain()
{
    m_data = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOut(0) : std::vector<float>();
}
