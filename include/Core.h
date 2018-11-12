#pragma once

#ifndef CORE_H
#define CORE_H

#include <glew.h>
#include <memory>
#include <vector>
#include <string>

class GameManager;
class Screen;

class Core
{
public:
	static void Initialise(int _argc, char* _argv[]);
	static void run();

	static std::shared_ptr<Screen> sWindow;
private:
	static void Core::KeyUpdate(unsigned char key, int x, int y);
	static void Core::KeyIn(int key, int x, int y);
	static void Core::KeyExit(unsigned char key, int x, int y);
	static void Core::KeyOut(int key, int x, int y);
	static void Core::idle();
	static void Core::display();
	static void reshape(int _width, int _height);
	static void Core::createVao();
	static void Core::createProgram();
	static GLuint vaoId;
	static GLuint positionVboId;
	static GLuint colorVboId;
	static GLuint programId;
	static GLuint vertexShaderId;
	static GLuint fragmentShaderId;
};

#endif