#pragma once

#ifndef INPUT_H
#define INPUT_H

#include <vector>

class Core;

class Input
{
	friend class Core;
public:
	static bool GetKey(int _iKey);
	static bool GetKeyDown(int _iKey);
	static bool GetKeyUp(int _iKey);
private:
	static std::vector<int> s_vecKeys;
	static std::vector<int> s_vecKeyUp;
	static std::vector<int> s_vecKeyDown;
};

#endif