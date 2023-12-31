#pragma once

#include <string>
#include <vector>
#include "includes/ToroImNodeFlow/ToroImNodeFlow.h"
#include "includes/imgui_bindings/imgui_stdlib.h"
#include "includes/header_only/csvparser.h"
#include "includes/ToroImGuiHandle/ToroImGuiHandle.h"
#include <nfd.hpp>


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

class MultiplyNode : public BaseNode
{
public:
	MultiplyNode() : BaseNode(ImNodeType_Middle) {}

	void render() override;

    std::vector<float> getOut(int index) override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	BasePin inB = BasePin(this, ImNode::PinKind::Input, false, "IN B");
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

    std::vector<float> m_data;
};

// ---------------------------------------------------------------------------------------------------------------------

class SubtractNode : public BaseNode
{
public:
	SubtractNode() : BaseNode(ImNodeType_Middle) {}

	void render() override;

    std::vector<float> getOut(int index) override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	BasePin inB = BasePin(this, ImNode::PinKind::Input, false, "IN B");
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

    std::vector<float> m_data;
};

// ---------------------------------------------------------------------------------------------------------------------

class DivideNode : public BaseNode
{
public:
	DivideNode() : BaseNode(ImNodeType_Middle) {}

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
