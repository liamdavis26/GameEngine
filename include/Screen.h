#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
	friend class Screen;
	friend class Camera;
public:
	Screen(int _width, int _height);
	static int GetWidth();
	static int GetHeight();
	static void SetResolution(int _width, int _height);

private:
	static int s_iWidth;
	static int s_iHeight;

};

#endif