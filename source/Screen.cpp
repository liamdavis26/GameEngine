#include "Screen.h"

int Screen::s_iWidth;
int Screen::s_iHeight;

Screen::Screen(int _width, int _height)
{
	SetResolution(_width, _height);
}

int Screen::GetWidth()
{
	return s_iWidth;
}

int Screen::GetHeight()
{
	return s_iHeight;
}

void Screen::SetResolution(int _width, int _height)
{
	s_iHeight = _height;
	s_iWidth = _width;
}