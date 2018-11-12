#include "Mesh.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

Mesh::Mesh()
{

}

void Mesh::LoadOBJ(std::string filename)
{
	// Find file
	std::ifstream inputFile(filename);

	if (inputFile.is_open())
	{
		// OBJ files can store texture coordinates, positions and normals
		std::vector<glm::vec2> rawUVData;
		std::vector<glm::vec3> rawPositionData;
		std::vector<glm::vec3> rawNormalData;

		std::string currentLine;

		while (std::getline(inputFile, currentLine))
		{
			std::stringstream currentLineStream(currentLine);
			//std::cout<< currentLine <<std::endl;

			if (!currentLine.substr(0, 2).compare(0, 2, "vt"))
			{
				std::string junk;
				float x, y;
				currentLineStream >> junk >> x >> y;
				rawUVData.push_back(glm::vec2(x, y));
			}
			else if (!currentLine.substr(0, 2).compare(0, 2, "vn"))
			{
				std::string junk;
				float x, y, z;
				currentLineStream >> junk >> x >> y >> z;
				rawNormalData.push_back(glm::vec3(x, y, z));
			}
			else if (!currentLine.substr(0, 2).compare(0, 1, "v"))
			{
				std::string junk;
				float x, y, z;
				currentLineStream >> junk >> x >> y >> z;
				rawPositionData.push_back(glm::vec3(x, y, z));
			}
			else if (!currentLine.substr(0, 2).compare(0, 1, "f"))
			{
				std::string junk;
				std::string verts[4];

				currentLineStream >> junk >> verts[0] >> verts[1] >> verts[2] >> verts[3];

				if (verts[3].empty())
				{
					for (unsigned int i = 0; i < 3; i++)
					{
						std::stringstream currentSection(verts[i]);

						// There is just position data
						unsigned int posID = 0;
						unsigned int uvID = 0;
						unsigned int normID = 0;

						if (verts[i].find('/') == std::string::npos)
						{
							// No texcoords or normals
							currentSection >> posID;
						}
						else if (verts[i].find("//") != std::string::npos)
						{
							// No texcoords
							char junk;
							currentSection >> posID >> junk >> junk >> normID;
						}
						else
						{
							char junk;
							currentSection >> posID >> junk >> uvID >> junk >> normID;
						}

						if (posID > 0)
						{
							m_vPositionData.push_back(rawPositionData[posID - 1]);
						}
						if (uvID > 0)
						{
							m_vUVData.push_back(rawUVData[uvID - 1]);
						}
						if (normID > 0)
						{
							m_vNormalData.push_back(rawNormalData[normID - 1]);
						}

					}
				}
				else
				{
					std::cerr << "WARNING: This OBJ loader only works with triangles but a quad has been detected. Please triangulate your mesh." << std::endl;
					inputFile.close();
					return;
				}

			}
		}

		inputFile.close();
	}

	m_glPosBuffer = 0;
	glGenBuffers(1, &m_glPosBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_glPosBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vPositionData.size() * 3, &m_vPositionData[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	if (m_vNormalData.size() > 0)
	{
		m_glPosBuffer = 0;
		glGenBuffers(1, &m_glNormalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_glNormalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vPositionData.size() * 3, &m_vNormalData[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
	}

	if (m_vUVData.size() > 0)
	{
		m_glUVBuffer = 0;
		glGenBuffers(1, &m_glUVBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_glUVBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vPositionData.size() * 2, &m_vUVData[0], GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(2);
	}
}