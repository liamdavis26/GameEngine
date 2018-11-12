#pragma once

#include "glew.h"
#include <glm.hpp>
#include <memory>
#include <vector>


class Mesh
{
public:
	Mesh();
	void LoadOBJ(std::string filename);

private:
	std::vector<glm::vec2> m_vUVData;
	std::vector<glm::vec3> m_vPositionData;
	std::vector<glm::vec3> m_vNormalData;

	GLuint m_glPosBuffer;
	GLuint m_glUVBuffer;
	GLuint m_glNormalBuffer;
};