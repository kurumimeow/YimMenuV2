#include "Items.hpp"

namespace YimMenu
{
	SameLineItem::SameLineItem(std::shared_ptr<UIItem> wrapped) :
		m_Wrapped(std::move(wrapped))
	{
	}

	void SameLineItem::Draw()
	{
		ImGui::SameLine();
		m_Wrapped->Draw();
	}

	bool SameLineItem::CanDraw()
	{
		return m_Wrapped && m_Wrapped->CanDraw();
	}
}