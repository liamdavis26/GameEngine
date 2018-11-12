#pragma once
#include "GameAsset.h"

class Component;
class Transform;

class Actor : public GameAsset
{
	friend class GameManager;
public:
	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (int i = 0; i < m_vComponents.size(); i++)
		{
			std::shared_ptr<T> c = dynamic_cast<T*>(m_vComponents.at(i).get());

			if (c != nullptr)
			{
				return c;
			}
		}

		return std::shared_ptr<T>();
	}
private:
	std::vector<std::shared_ptr<Component>> m_vComponents;

	virtual void OnAwake();
	virtual void OnUpdate();
	virtual void OnPostRender();
	virtual void OnDestroy();

	template <typename T>
	void AddComponent(std::shared_ptr<T> _cAdd)
	{
		m_vComponents.push_back(_cAdd);
		_cAdd->SetParent(GameManager::GetActor(m_iAssetID));
		_cAdd->Awake();
	}

	std::weak_ptr<Component> GetComponent(int _iID);
};