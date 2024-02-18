#pragma once

#include <string>
#include <vector>

#include <ImGuiHandler.h>
#include <ImNodeFlow.h>
#include "nfd.hpp"
#include "imgui_stdlib.h"
#include "csvparser.h"

using namespace ImFlow;

enum FlexPlotFilters
{
    FlexPlotFilters_Vector = ConnectionFilter_MakeCustom
};

class CsvReader : public BaseNode
{
public:
    CsvReader()
    {
        addOUT<std::vector<float>>("Col", FlexPlotFilters_Vector)->behaviour([this](){
            return m_data;
        });
    }

    void draw() override;

private:
    std::string m_filepath;
    rapidcsv::Document m_doc;
    std::vector<std::string> m_columnsName;
    int m_selectedCol = 0;

    std::vector<float> m_data;
};