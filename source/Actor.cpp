#include "Actor.h"
#include "Component.h"

void Actor::OnAwake()
{
	for (size_t i = 0; i < m_vComponents.size(); i++)
	{
		m_vComponents.at(i)->Awake();
	}
}

void Actor::OnUpdate()
{
	for (size_t i = 0; i < m_vComponents.size(); i++)
	{
		if (m_vComponents.at(i)->GetDestroyed() == true)
		{
			m_vComponents.at(i)->Destroy();
			m_vComponents.erase(m_vComponents.begin() + i);
			i--;
		}
		else
		{
			m_vComponents.at(i)->Update();
		}
	}
}

void Actor::OnPostRender()
{
	for (size_t i = 0; i < m_vComponents.size(); i++)
	{
		m_vComponents.at(i)->PostRender();
	}
}

void Actor::OnDestroy()
{
	for (size_t i = 0; i < m_vComponents.size(); i++)
	{
		m_vComponents.at(i)->Destroy();
		m_vComponents.erase(m_vComponents.begin() + i);
		i--;
	}
}

std::weak_ptr<Component> Actor::GetComponent(int _iID)
{
	for (size_t i = 0; i < m_vComponents.size(); i++)
	{
		if (m_vComponents.at(i)->GetID() == _iID)
		{
			return m_vComponents.at(i);
		}
	}

	return std::weak_ptr<Component>();
}