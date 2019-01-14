#pragma once
#include <iostream>
#define MAX_KEYS 256
class Input
{
public:
	Input();
	~Input();
	void setKeyDown(int keyCode);
	void setKeyUp(int keyCode);
	bool GetKeyDown(int keycode);

private:
	bool keys[MAX_KEYS];
	
};
