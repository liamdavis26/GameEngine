#include <glew.h>
#include <freeglut.h>
#include "Core.h"
#include "Screen.h"
#include "Input.h"
#include "GameManager.h"

std::shared_ptr<Screen> Core::sWindow;
GLuint Core::positionVboId;
GLuint Core::colorVboId;
GLuint Core::vaoId;
GLuint Core::programId;
GLuint Core::vertexShaderId;
GLuint Core::fragmentShaderId;

void Core::idle()
{
	for (std::size_t i = 0; i < GameManager::m_vActors.size(); i++)
	{
		GameManager::m_vActors.at(i)->Update();
	}
}

void Core::display()
{
	glClearColor(32.0f / 255.0f, 32.0f / 255.0f, 32.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, sWindow->GetWidth(), sWindow->GetHeight());

	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void Core::reshape(int width, int height)
{
	Screen::SetResolution(width, height);

	idle();
}

//Initialises glew and glut
void Core::Initialise(int _argc, char* _argv[])
{
	//Initialise glut
	glutInit(&_argc, _argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Game Engine");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//Idle function runs while no new events
	glutIdleFunc(idle);

	//Scrren management functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	//Input functions.
	glutKeyboardFunc(KeyUpdate);
	glutKeyboardUpFunc(KeyExit);
	glutSpecialFunc(KeyIn);
	glutSpecialUpFunc(KeyOut);

	//Set screen.
	sWindow->SetResolution(800, 600);

	//Initialise glew
	glewInit();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	createVao();
	createProgram();
}

void Core::run()
{
	glutMainLoop();
}

void Core::KeyUpdate(unsigned char key, int x, int y)
{
	KeyIn(key, x, y);
}

void Core::KeyIn(int key, int x, int y)
{
	for (std::size_t i = 0; i < Input::s_vecKeys.size(); i++)
	{
		Input::s_vecKeys.push_back(key);
		Input::s_vecKeyDown.push_back(key);
	}
}

void Core::KeyExit(unsigned char key, int x, int y)
{
	KeyOut(key, x, y);
}

void Core::KeyOut(int key, int x, int y)
{
	for (std::size_t i = 0; i < Input::s_vecKeys.size(); i++)
	{
		if (Input::s_vecKeys.at(i) == key)
		{
			Input::s_vecKeys.erase(Input::s_vecKeys.begin() + i);
			i--;
		}
	}

	Input::s_vecKeyUp.push_back(key);
}

void Core::createVao()
{
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	GLfloat vertices[] = {
		-0.8f, -0.8f, 0.0f, 1.0f,
		0.0f, 0.8f, 0.0f, 1.0f,
		0.8f, -0.8f, 0.0f, 1.0f
	};

	glGenBuffers(1, &positionVboId);
	glBindBuffer(GL_ARRAY_BUFFER, positionVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};

	glGenBuffers(1, &colorVboId);
	glBindBuffer(GL_ARRAY_BUFFER, colorVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}

void Core::createProgram()
{
	const GLchar* vertexShader =
	{
		"#version 400\n\
		layout(location = 0) in vec4 vPosition;\n\
		layout(location = 1) in vec3 vNormalIn;\n\
		layout(location = 2) in vec2 vTexCoordIn;\n\
		\n\
		uniform mat4 modelMat;\n\
		uniform mat4 viewMat;\n\
		uniform mat4 projMat;\n\
		\n\
		out vec4 ex_Color;\n\
		void main(void)\n\
		{\n\
		 gl_Position = projMat * viewMat * modelMat * vPosition;\n\
		 ex_Color = in_Color;\n\
		}\n"
	};

	vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShader, NULL);
	glCompileShader(vertexShaderId);

	const GLchar* fragmentShader =
	{
		"#version 400\n"\

		"in vec4 ex_Color;\n"\
		"out vec4 out_Color;\n"\

		"void main(void)\n"\
		"{\n"\
		" out_Color = ex_Color;\n"\
		"}\n"
	};

	fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderId, 1, &fragmentShader, NULL);
	glCompileShader(fragmentShaderId);

	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);
	glLinkProgram(programId);
	glUseProgram(programId);
}