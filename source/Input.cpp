#include "Input.h"

std::vector<int> Input::s_vecKeys;
std::vector<int> Input::s_vecKeyUp;
std::vector<int> Input::s_vecKeyDown;


bool Input::GetKey(int _iKey)
{
	for (size_t i = 0; i < s_vecKeys.size(); i++)
	{
		if (s_vecKeys.at(i) == _iKey)
		{
			return true;
		}
	}

	return false;
}

bool Input::GetKeyDown(int _iKey)
{
	for (size_t i = 0; i < s_vecKeyUp.size(); i++)
	{
		if (s_vecKeyUp.at(i) == _iKey)
		{
			return true;
		}
	}

	return false;
}

bool Input::GetKeyUp(int _iKey)
{
	for (size_t i = 0; i < s_vecKeyDown.size(); i++)
	{
		if (s_vecKeyDown.at(i) == _iKey)
		{
			return true;
		}
	}

	return false;
}