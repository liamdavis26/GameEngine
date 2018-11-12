#include "Camera.h"
#include "Screen.h"
#include "gtc/matrix_transform.hpp"

glm::mat4x4 Camera::GetProjMatrix()
{
	if (m_matProjection != NULL)
	{
		return *m_matProjection;
	}

	if (m_bOrtho == true)
	{
		return glm::ortho(0.0f, (float)Screen::GetWidth(), (float)Screen::GetHeight(), 0.0f);
	}
	else
	{
		return glm::perspective(m_fFov, (float)Screen::GetWidth() / (float)Screen::GetHeight(), m_fNear, m_fFar);
	}
}

void Camera::SetProjMatrix(glm::mat4x4 _matProj)
{
	this->m_matProjection = new glm::mat4x4();
	*this->m_matProjection = _matProj;
}

void Camera::ResetProjMatrix()
{
	m_matProjection = NULL;
}