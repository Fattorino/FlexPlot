#pragma once

#include <string>
#include <vector>

#include "ToroImGuiHandle.hpp"
#include "ToroImNodeFlow.h"
#include "nfd.hpp"
#include "imgui_stdlib.h"
#include "csvparser.h"

class CsvColumnReader : public BaseNode
{
public:
    CsvColumnReader() : BaseNode(ImNodeType_Start, 200.f) {}

	void render() override;

    std::vector<float> getOut(int index) override;

private:
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

    std::string m_filepath;
    rapidcsv::Document m_doc;
    std::vector<std::string> m_columnsName;
    int m_selectedCol = 0;

    std::vector<float> m_data;
};

// ---------------------------------------------------------------------------------------------------------------------

class SumNode : public BaseNode
{
public:
	SumNode() : BaseNode(ImNodeType_Middle) {}

	void render() override;

    std::vector<float> getOut(int index) override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	BasePin inB = BasePin(this, ImNode::PinKind::Input, false, "IN B");
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

    std::vector<float> m_data;
};

// ---------------------------------------------------------------------------------------------------------------------

class ReadNode : public BaseNode
{
public:
	ReadNode() : BaseNode(ImNodeType_End, 100.f) {}

	void render() override;

	void resolveChain() override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
    std::vector<float> m_data;
};
