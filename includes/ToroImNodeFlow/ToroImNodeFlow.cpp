#include "ToroImNodeFlow.h"

ImNodeFlow INF;

// ---------------------------------------------------------------------------------------------------------------------

void BasePin::render()
{
	if (m_kind == ImNode::PinKind::Output && m_parent->getWidth() > 0.f)
	{
		ImGui::Indent(m_parent->getWidth() - ImGui::CalcTextSize(m_text.c_str()).x);
	}
	ImNode::BeginPin(m_id, m_kind);
	ImGui::Text(m_text.c_str());
	ImNode::EndPin();
	if (m_kind == ImNode::PinKind::Output && m_parent->getWidth() > 0.f)
	{
		ImGui::Unindent(m_parent->getWidth() - ImGui::CalcTextSize(m_text.c_str()).x);
	}
}

// ---------------------------------------------------------------------------------------------------------------------

bool ImNodeFlow::m_validateMuliLink(BasePin* fromPinPtr, BasePin* toPinPtr)
{
	if (!fromPinPtr->canMultiLink())
	{
		for (auto& node : m_nodeLinks)
		{
			if (node.fromPin == fromPinPtr || node.toPin == fromPinPtr)
				return false;
		}
	}

	if (!toPinPtr->canMultiLink())
	{
		for (auto& node : m_nodeLinks)
		{
			if (node.fromPin == toPinPtr || node.toPin == toPinPtr)
				return false;
		}
	}

	return true;
}

bool ImNodeFlow::m_validateLink(BasePin* fromPinPtr, BasePin* toPinPtr)
{
	if (fromPinPtr->isInput() != toPinPtr->isInput() && fromPinPtr->getParent() != toPinPtr->getParent() && m_validateMuliLink(fromPinPtr, toPinPtr))
	{
		return true;
	}
	return false;
}

void ImNodeFlow::init()
{
    ImNode::Config config;
    config.SettingsFile = "Simple.json";
    m_editorContext = ImNode::CreateEditor(&config);
	ImNode::SetCurrentEditor(m_editorContext);
}

void ImNodeFlow::destroy()
{
	ImNode::SetCurrentEditor(nullptr);
    ImNode::DestroyEditor(m_editorContext);
}

void ImNodeFlow::update()
{
	// ImNode::SetCurrentEditor(m_editorContext);
	ImNode::Begin("FLexPlotEditor", ImVec2(0.0, 0.0f));

	for (auto& node : m_nodes)
	{
		node->render();
	}

	// Submit Links
	for (auto& link : m_nodeLinks)
		ImNode::Link(link.id, link.fromPin->getID(), link.toPin->getID());

	// Handle Link Creation
	if (ImNode::BeginCreate())
	{
		ImNode::PinId fromPinId, toPinId;
		if (ImNode::QueryNewLink(&fromPinId, &toPinId) && fromPinId && toPinId)
		{
			BasePin* fromPinPtr = reinterpret_cast<BasePin*>(fromPinId.Get());
			BasePin* toPinPtr = reinterpret_cast<BasePin*>(toPinId.Get());

			if (m_validateLink(fromPinPtr, toPinPtr))
			{
				// ImNode::AcceptNewItem() return true when user release mouse button.
				if (ImNode::AcceptNewItem())
				{
					if (!fromPinPtr->isInput())
						m_nodeLinks.emplace_back(&m_uniqueID, fromPinPtr, toPinPtr);
					else
						m_nodeLinks.emplace_back(&m_uniqueID, toPinPtr, fromPinPtr);

					// Draw new link.
					ImNode::Link(m_nodeLinks.back().id, m_nodeLinks.back().fromPin->getID(), m_nodeLinks.back().toPin->getID());
				}
			}
		}
	}
	ImNode::EndCreate();

	// Handle Link Deletion
	if (ImNode::BeginDelete())
	{
		// There may be many links marked for deletion, let's loop over them.
		ImNode::LinkId deletedLinkId;
		while (ImNode::QueryDeletedLink(&deletedLinkId))
		{
			// If you agree that link can be deleted, accept deletion.
			if (ImNode::AcceptDeletedItem())
			{
				for (int i = 0; i < m_nodeLinks.size(); i++)
				{
					if (m_nodeLinks[i].id == deletedLinkId)
					{
						m_nodeLinks.erase(m_nodeLinks.begin() + i);
						break;
					}
				}
			}
			// You may reject link deletion by calling:
			// ImNode::RejectDeletedItem();
		}
	}
	ImNode::EndDelete();

	ImNode::End();
	// ImNode::SetCurrentEditor(nullptr);

	// RESOLVE ENDS
	for (auto& node : m_nodes)
	{
		if (node->getNodeType() == ImNodeType_End)
		{
			node->resolveChain();
		}
	}
}
