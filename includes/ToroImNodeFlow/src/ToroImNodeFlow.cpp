#include "ToroImNodeFlow.h"

bool ImNodeFlow::m_validateMultiLink(BasePin* fromPinPtr, BasePin* toPinPtr)
{
	if (!fromPinPtr->canMultiLink())
	{
		for (auto& link : m_nodeLinks)
		{
			if (link->fromPin == fromPinPtr || link->toPin == fromPinPtr)
				return false;
		}
	}

	if (!toPinPtr->canMultiLink())
	{
		for (auto& link : m_nodeLinks)
		{
			if (link->fromPin == toPinPtr || link->toPin == toPinPtr)
				return false;
		}
	}

	return true;
}

bool ImNodeFlow::m_validateLink(BasePin* fromPinPtr, BasePin* toPinPtr)
{
	if (fromPinPtr->isInput() != toPinPtr->isInput() && fromPinPtr->getParent() != toPinPtr->getParent() &&
            m_validateMultiLink(fromPinPtr, toPinPtr))
	{
		return true;
	}
	return false;
}

void ImNodeFlow::init(std::vector<std::shared_ptr<BaseNode>>& nodes)
{
    ImNode::Config config;
    config.SettingsFile = "Simple.json";
    m_editorContext = ImNode::CreateEditor(&config);
	ImNode::SetCurrentEditor(m_editorContext);

    m_uniqueID = 1;
    m_nodes = nodes;
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
		ImNode::Link(link->id, link->fromPin->getID(), link->toPin->getID());

	// Handle Link Creation
	if (ImNode::BeginCreate())
	{
		ImNode::PinId fromPinId, toPinId;
		if (ImNode::QueryNewLink(&fromPinId, &toPinId) && fromPinId && toPinId)
		{
			auto* fromPinPtr = reinterpret_cast<BasePin*>(fromPinId.Get());
			auto* toPinPtr = reinterpret_cast<BasePin*>(toPinId.Get());

			if (m_validateLink(fromPinPtr, toPinPtr))
			{
				// ImNode::AcceptNewItem() return true when user release mouse button.
				if (ImNode::AcceptNewItem())
				{
					if (toPinPtr->isInput())
                    {
                        auto* link = new BaseLink(&m_uniqueID, fromPinPtr, toPinPtr);
						m_nodeLinks.emplace_back(link);
                        toPinPtr->setLink(link);
                    }
					else
                    {
                        auto* link = new BaseLink(&m_uniqueID, toPinPtr, fromPinPtr);
                        m_nodeLinks.emplace_back(link);
                        fromPinPtr->setLink(link);
                    }

					// Draw new link.
					ImNode::Link(m_nodeLinks.back()->id, m_nodeLinks.back()->fromPin->getID(), m_nodeLinks.back()->toPin->getID());
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
                for (auto& link : m_nodeLinks)
                {
                    if (link->id == deletedLinkId)
                    {
                        link->toPin->setLink(nullptr);
                        delete link;
                        link = nullptr;
                    }
                }
                m_nodeLinks.erase(std::remove(m_nodeLinks.begin(), m_nodeLinks.end(), nullptr), m_nodeLinks.end());
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
