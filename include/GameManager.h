#pragma once
#include "Actor.h"

class Camera;

class GameManager
{
	friend class Actor;
public:
	std::shared_ptr<Actor> CreateActor();
	static std::vector<std::shared_ptr<Actor>> m_vActors;

	template <typename T>
	std::shared_ptr<T> CreateComponent()
	{
		std::shared_ptr<T> c = std::make_shared<T>(m_iComponentID);
		m_iComponentID++;
		return c;
	}

	static std::weak_ptr<Actor> GetActor(int _iActorID);
	void DestroyActor(int _iActorID);
	void DestroyActor(std::shared_ptr<Actor> _sActor);
	void DestroyComponent(int _iComponentID);
	std::shared_ptr<Camera> GetMain();
	void SetMain(std::shared_ptr<Camera> _sCam);
private:
	static int m_iActorID;
	static int m_iComponentID;
	static std::shared_ptr<Camera> m_cMain;
};