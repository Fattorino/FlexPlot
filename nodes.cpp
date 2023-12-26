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

float DummyNode::getOutPin(int index)
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

float SumNode::getOutPin(int index)
{
	float res = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOutPin(0) : 0.0f;
    res += (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOutPin(0) : 0.0f;

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

float MultiplyNode::getOutPin(int index)
{
	float res = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOutPin(0) : 1.0f;
    res *= (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOutPin(0) : 1.0f;

	return res;
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

float SubtractNode::getOutPin(int index)
{
	float res = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOutPin(0) : 0.0f;
    res -= (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOutPin(0) : 0.0f;

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

float DivideNode::getOutPin(int index)
{
	float res = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOutPin(0) : 1.0f;
    res /= (inB.getLink()) ? inB.getLink()->fromPin->getParent()->getOutPin(0) : 1.0f;

	return res;
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
    val = (inA.getLink()) ? inA.getLink()->fromPin->getParent()->getOutPin(0) : -10.0f;
}
