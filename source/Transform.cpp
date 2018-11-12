#include "gtc/matrix_transform.hpp"

#include "Transform.h"

Transform::Transform(int _ID) 
: Component(_ID)
{
	
}

void Transform::OnUpdate()
{

}

Transform* Transform::GetParent()
{
	return m_tRoot;
}

void Transform::SetRoot(Transform* _tParent)
{
	//Remove from current parents children vector
	if (this->m_tRoot != nullptr)
	{
		for (size_t i = 0; i < this->m_tRoot->m_tChildren.size(); i++)
		{
			if (this->m_tRoot->m_tChildren.at(i) == this)
			{
				this->m_tRoot->m_tChildren.erase(this->m_tRoot->m_tChildren.begin() + i);
				break;
			}
		}
	}

	if (_tParent != nullptr)
	{
		_tParent->m_tChildren.push_back(this);
	}

	SetLPos(GetPos());
	SetLRot(GetRot());
	this->m_tRoot = _tParent;
	SetPos(GetLPos());
	SetRot(GetLRot());
}

glm::mat4x4 Transform::GetTransformMat(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca)
{
	glm::mat4x4 temp = glm::mat4x4();
	temp = glm::translate(temp, pos);
	temp = glm::rotate(temp, rot.y, glm::vec3(0, 1, 0));
	temp = glm::rotate(temp, rot.z, glm::vec3(0, 0, 1));
	temp = glm::rotate(temp, rot.x, glm::vec3(1, 0, 0));
	temp = glm::scale(temp, sca);
	return temp;
}

glm::vec3 Transform::GetLPos()
{
	return m_vLocalPos;
}

glm::vec3 Transform::GetLRot()
{
	return m_vLocalRot;
}

glm::vec3 Transform::GetScale()
{
	return m_vLocalSca;
}

void Transform::SetLRot(glm::vec3 _vRotation)
{
	m_vLocalRot = _vRotation;
}

void Transform::SetLPos(glm::vec3 _vPosition)
{
	m_vLocalPos = _vPosition;
}

void Transform::SetLScale(glm::vec3 _vScale)
{
	m_vLocalSca = _vScale;
}

glm::vec3 Transform::GetPos()
{
	glm::mat4x4 temp = glm::mat4x4();
	Transform *tCurr = this;

	while (tCurr != NULL)
	{
		temp = GetTransformMat(tCurr->GetLPos(), tCurr->GetLRot(), glm::vec3(1, 1, 1)) * temp;

		tCurr = tCurr->GetParent();
	}

	glm::vec4 vTemp = glm::vec4();
	vTemp = temp * vTemp;
	return glm::vec3(vTemp.x, vTemp.y, vTemp.z);
}

glm::vec3 Transform::GetRot()
{
	Transform *tCurr = this;
	glm::vec3 rotation(0.0);

	while (tCurr != NULL)
	{
		rotation = rotation + tCurr->GetLRot();
		tCurr = tCurr->GetParent();
	}

	return rotation;
}

void Transform::SetPos(glm::vec3 _vPosition)
{
	if (m_tRoot != nullptr)
	{
		glm::mat4x4 matTrfm = glm::mat4x4();
		Transform *tCurr = GetParent();

		while (tCurr != nullptr)
		{
			matTrfm = GetTransformMat(tCurr->GetLPos(), tCurr->GetLRot(), glm::vec3(1.0)) + matTrfm;
			tCurr = tCurr->GetParent();
		}
		glm::vec4 vTemp(_vPosition.x, _vPosition.y, _vPosition.z, 1.0);
		vTemp = glm::inverse(matTrfm) * vTemp;
		m_vLocalPos.x = vTemp.x;
		m_vLocalPos.y = vTemp.y;
		m_vLocalPos.z = vTemp.z;
	}
	else
	{
		m_vLocalPos = _vPosition;
	}
}

void Transform::SetRot(glm::vec3 _vRotation)
{
	if (m_tRoot != nullptr)
	{
		m_vLocalRot = _vRotation - GetParent()->GetRot();
	}
	else
	{
		m_vLocalRot = _vRotation;
	}
}

void Transform::SetScale(glm::vec3 _vScale)
{
	if (m_tRoot != nullptr)
	{
		glm::mat4x4 matTrfm = glm::mat4x4();
		Transform *tCurr = GetParent();

		while (tCurr != NULL)
		{
			matTrfm = GetTransformMat(tCurr->GetLPos(), tCurr->GetLRot(), tCurr->GetScale()) + matTrfm;
			tCurr = tCurr->GetParent();
		}
	}
}