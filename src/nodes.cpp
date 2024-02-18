#include "nodes.h"

void CsvReader::draw()
{
    ImGui::SetNextItemWidth(150.f);
    ImGui::InputTextWithHint("##InputCsvPath", "Fil path (.csv)", &m_filepath);
    ImGui::SameLine();
    if(ImGui::Button("Search"))
    {
        NFD_Init();
        nfdchar_t *outPath;
        nfdfilteritem_t filterItem[1] = { { "Telemetry", "csv,txt" } };
        nfdresult_t result = NFD_OpenDialog(&outPath, filterItem, 1, NULL);
        if (result == NFD_OKAY)
        {
            m_filepath = outPath;
            NFD_FreePath(outPath);
        }
        NFD_Quit();
    }
    if(ImGui::Button("Load"))
    {
        m_doc.Load(m_filepath);
        m_columnsName = m_doc.GetColumnNames();
    }

    ImGui::SetNextItemWidth(150.f);
    ImToro::vCombo("Column", &m_selectedCol, m_columnsName);

    if(ImGui::Button("Refresh"))
    {
        m_data = m_doc.GetColumn<float>(m_selectedCol);
    }
}
