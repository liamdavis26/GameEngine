#include "Component.h"

Component::Component(int _iComponentID)
{
	SetID(_iComponentID);
}

std::weak_ptr<Actor> Component::GetParent()
{
	return m_aParent;
}

void Component::SetParent(std::weak_ptr<Actor> _Parent)
{
	m_aParent = _Parent;
}