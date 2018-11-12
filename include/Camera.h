#pragma once
#include <glm.hpp>

#include "Component.h"

class Camera: public Component
{
public:
	glm::mat4x4 GetProjMatrix();
	void SetProjMatrix(glm::mat4x4 _matProj);
	void ResetProjMatrix();
private:
	glm::mat4x4* m_matProjection;
	float m_fFov;
	bool m_bOrtho;
	float m_fOrthoSize;
	float m_fNear;
	float m_fFar;
};