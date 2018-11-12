#include "GameManager.h"

#include "Transform.h"

std::vector<std::shared_ptr<Actor>> GameManager::m_vActors;
int GameManager::m_iActorID;
int GameManager::m_iComponentID;
std::shared_ptr<Camera> GameManager::m_cMain;

std::weak_ptr<Actor> GameManager::GetActor(int _iActorID)
{
	for (size_t i = 0; i < m_vActors.size(); i++)
	{
		if (m_vActors.at(i)->GetID() == _iActorID)
		{
			return m_vActors.at(i);
		}
	}
}

std::shared_ptr<Actor> GameManager::CreateActor()
{
	std::shared_ptr<Actor> c = std::make_shared<Actor>();
	c->SetID(m_iActorID);
	c->AddComponent(CreateComponent<Transform>());
	m_vActors.push_back(c);
	m_iActorID++;

	return c;
}

void GameManager::DestroyActor(int _iActorID)
{
	for (size_t i = 0; i < m_vActors.size(); i++)
	{
		if (m_vActors.at(i)->GetID() == _iActorID)
		{
			m_vActors.at(i)->SetDetroyed(true);
		}
	}
}

void GameManager::DestroyActor(std::shared_ptr<Actor> _sActor)
{
	for (size_t i = 0; i < m_vActors.size(); i++)
	{
		if (m_vActors.at(i) == _sActor)
		{
			m_vActors.at(i)->SetDetroyed(true);
			break;
		}
	}
}

void GameManager::DestroyComponent(int _iComponentID)
{
	std::weak_ptr<Component> c;
	for (size_t i = 0; i < m_vActors.size(); i++)
	{
		for (size_t j = 0; j < m_vActors.at(i)->m_vComponents.size(); j++)
		{
			if (m_vActors.at(i)->m_vComponents.at(i)->GetID() == _iComponentID)
			{
				m_vActors.at(i)->m_vComponents.at(i)->SetDetroyed(true);
				break;
			}
		}
	}
}

std::shared_ptr<Camera> GameManager::GetMain()
{
	return m_cMain;
}

void GameManager::SetMain(std::shared_ptr<Camera> _sCam)
{
	m_cMain = _sCam;
}