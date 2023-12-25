#pragma once

#include <string>
#include <vector>
#include "includes/ToroImNodeFlow/ToroImNodeFlow.h"


class DummyNode : public BaseNode
{
public:
	DummyNode() : BaseNode(ImNodeType_Start, 200.f) {}

	virtual void render();

	virtual float getOutPinVal(int index = 0) override;

private:
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");
	float val = 0.f;
};

// ---------------------------------------------------------------------------------------------------------------------

class SumNode : public BaseNode
{
public:
	SumNode() : BaseNode(ImNodeType_Middle) {}

	virtual void render();

	virtual float getOutPinVal(int index = 0) override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	BasePin inB = BasePin(this, ImNode::PinKind::Input, false, "IN B");
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

};

// ---------------------------------------------------------------------------------------------------------------------

class MultiplyNode : public BaseNode
{
public:
	MultiplyNode() : BaseNode(ImNodeType_Middle) {}

	virtual void render();

	virtual float getOutPinVal(int index = 0) override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	BasePin inB = BasePin(this, ImNode::PinKind::Input, false, "IN B");
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

};

// ---------------------------------------------------------------------------------------------------------------------

class SubtractNode : public BaseNode
{
public:
	SubtractNode() : BaseNode(ImNodeType_Middle) {}

	virtual void render();

	virtual float getOutPinVal(int index = 0) override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	BasePin inB = BasePin(this, ImNode::PinKind::Input, false, "IN B");
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

};

// ---------------------------------------------------------------------------------------------------------------------

class DivideNode : public BaseNode
{
public:
	DivideNode() : BaseNode(ImNodeType_Middle) {}

	virtual void render();

	virtual float getOutPinVal(int index = 0) override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	BasePin inB = BasePin(this, ImNode::PinKind::Input, false, "IN B");
	BasePin out = BasePin(this, ImNode::PinKind::Output, true, "OUT");

};

// ---------------------------------------------------------------------------------------------------------------------

class ReadNode : public BaseNode
{
public:
	ReadNode() : BaseNode(ImNodeType_End, 100.f) {}

	virtual void render();

	virtual void resolveChain() override;

private:
	BasePin inA = BasePin(this, ImNode::PinKind::Input, false, "IN A");
	float val = 0.f;
};
