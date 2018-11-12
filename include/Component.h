#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameAsset.h"

class Actor;

class Component : public GameAsset
{
public:
	std::weak_ptr<Actor> GetParent();
	void SetParent(std::weak_ptr<Actor> _Parent);
protected:
	Component(int _iComponentID);
	std::weak_ptr<Actor> m_aParent;
};
#endif

