#pragma once

#include "Component.h"

class RenderComponent : public Component
{
public:
	void Render();
protected:
	virtual void OnRender();
};