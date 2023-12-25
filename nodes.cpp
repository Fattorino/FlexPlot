#include "nodes.h"

void DummyNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));
	ImGui::Text("Dummy input float");

	ImGui::SetNextItemWidth(70.f);
	ImGui::DragFloat(std::to_string(getID().Get()).c_str(), &val);
	ImGui::SameLine();
	out.render();

	ImNode::EndNode();
}

float DummyNode::getOutPinVal(int index)
{
	return val;
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

float SumNode::getOutPinVal(int index)
{
	float res = 0.f;
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inA)
			res += node.fromPin->getParent()->getOutPinVal();
	}
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inB)
			res += node.fromPin->getParent()->getOutPinVal();
	}
	return res;
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

float MultiplyNode::getOutPinVal(int index)
{
	float a = 0.f, b = 0.f;
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inA)
			a = node.fromPin->getParent()->getOutPinVal();
	}
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inB)
			b = node.fromPin->getParent()->getOutPinVal();
	}
	return a * b;
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

float SubtractNode::getOutPinVal(int index)
{
	float res = 0.f;
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inA)
			res = node.fromPin->getParent()->getOutPinVal();
	}
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inB)
			res -= node.fromPin->getParent()->getOutPinVal();
	}
	return res;
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

float DivideNode::getOutPinVal(int index)
{
	float a = 0.f, b = 0.f;
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inA)
			a = node.fromPin->getParent()->getOutPinVal();
	}
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inB)
			b = node.fromPin->getParent()->getOutPinVal();
	}
	return a / b;
}

// ---------------------------------------------------------------------------------------------------------------------

void ReadNode::render()
{
	ImNode::BeginNode(getID());

	ImGui::Dummy(ImVec2(getWidth(), 0.f));
	ImGui::Text("IN VAL:");

	inA.render();
	ImGui::SameLine();
	ImGui::Text("%f", val);

	ImNode::EndNode();
}

void ReadNode::resolveChain()
{
	val = 0.f;
	for (auto& node : getNodeLinks())
	{
		if (node.toPin == &inA)
			val = node.fromPin->getParent()->getOutPinVal();
	}
}
