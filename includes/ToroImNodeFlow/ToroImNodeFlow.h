#pragma once

#include <imgui.h>
#include <vector>
#include <functional>
#include <memory>

#include "ImNodeEditor/imgui_node_editor.h"
#include "ImNodeEditor/imgui_node_editor_internal.h"

namespace ImNode = ax::NodeEditor;

class BasePin;
class BaseLink;
class BaseNode;

enum ImNodeType
{
	ImNodeType_Start,
	ImNodeType_Middle,
	ImNodeType_End
};

// ---------------------------------------------------------------------------------------------------------------------

class ImNodeFlow
{
public:
	friend class BaseNode;

	ImNodeFlow() {}

	void init();
	void destroy();

	void update();

	std::vector<std::shared_ptr<BaseNode>>& getNodesList() { return m_nodes; }

    template<typename T>
    void pushNode(ImVec2 pos = ImVec2(0.f, 0.f), bool convert = false);

private:
	ImNode::EditorContext* m_editorContext = nullptr;
	// ImNode::Detail::EditorContext* m_editorContext = nullptr;

	std::vector<std::shared_ptr<BaseNode>> m_nodes;
	int m_uniqueID = 1;
	std::vector<BaseLink> m_nodeLinks;

	bool m_validateMuliLink(BasePin* fromPinPtr, BasePin* toPinPtr);
	bool m_validateLink(BasePin* fromPinPtr, BasePin* toPinPtr);

};

extern ImNodeFlow INF;

// ---------------------------------------------------------------------------------------------------------------------

class BasePin
{
public:
	BasePin(BaseNode* parent, ImNode::PinKind kind, bool allowMultuLink, std::string text)
	{
		m_parent = parent;
		m_kind = kind;
		m_allowMultuLink = allowMultuLink;
		m_text = text;
	}

	void render();

	bool isInput() { return m_kind == ImNode::PinKind::Input; }

	ImNode::PinId getID() { return m_id; }
	BaseNode* getParent() { return m_parent; }
	bool canMultiLink() { return m_allowMultuLink; }

private:
	uintptr_t m_id = reinterpret_cast<uintptr_t>(this);

	BaseNode* m_parent;
	ImNode::PinKind m_kind;
	bool m_allowMultuLink;
	std::string m_text;

};

// ---------------------------------------------------------------------------------------------------------------------

class BaseLink
{
public:
	BaseLink(int* id, BasePin* fromPin, BasePin* toPin)
	{
		this->id = *id;
		*id += 1;
		this->fromPin = fromPin;
		this->toPin = toPin;
	}

	ImNode::LinkId id;
	BasePin* fromPin;
	BasePin* toPin;
};

// ---------------------------------------------------------------------------------------------------------------------

class BaseNode
{
public:
	BaseNode(int nodeType, float width = 0.f)
	{
		m_id = INF.m_uniqueID++;
		m_nodeType = nodeType;
		m_width = width;
	}

	virtual void render() = 0;

	virtual float getOutPinVal(int index = 0) { return 0.f; }
	virtual void resolveChain() {}

	ImNode::NodeId getID() { return m_id; }
	int getNodeType() { return m_nodeType; }
	float getWidth() { return m_width; }

	std::vector<BaseLink>& getNodeLinks() { return INF.m_nodeLinks; }

private:
	ImNode::NodeId m_id;
	int m_nodeType;
	float m_width;
};

// ---------------------------------------------------------------------------------------------------------------------

template<typename T>
void ImNodeFlow::pushNode(ImVec2 pos, bool convert)
{
    static_assert(std::is_base_of<BaseNode, T>::value, "Pushed type is not subclass of BaseNode!");
    m_nodes.emplace_back(std::make_shared<T>());
    if (convert)
        ImNode::SetNodePosition(m_nodes.back()->getID(), reinterpret_cast<ImNode::Detail::EditorContext*>(m_editorContext)->ToCanvas(pos));
    else
        ImNode::SetNodePosition(m_nodes.back()->getID(), pos);
}
