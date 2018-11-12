#pragma once
#include <glm.hpp>

#include "Component.h"

class Transform : public Component
{
public:
	Transform(int _ID);
	Transform* GetParent();
	void SetRoot(Transform* _tRoot);

	glm::vec3 GetLPos();
	glm::vec3 GetLRot();
	glm::vec3 GetPos();
	glm::vec3 GetRot();
	glm::vec3 GetScale();
	glm::mat4x4 Transform::GetTransformMat(glm::vec3 pos, glm::vec3 rot, glm::vec3 sca);

	void SetPos(glm::vec3 _vPosition);
	void SetRot(glm::vec3 _vRotation);
	void SetScale(glm::vec3 _vScale);
	void SetLPos(glm::vec3 _vPosition);
	void SetLRot(glm::vec3 _vRotation);
	void SetLScale(glm::vec3 _vScale);
	void OnUpdate();
private:
	Transform* m_tRoot;
	std::vector<Transform*> m_tChildren;
	glm::vec3 m_vLocalPos;
	glm::vec3 m_vLocalRot;
	glm::vec3 m_vLocalSca;
};