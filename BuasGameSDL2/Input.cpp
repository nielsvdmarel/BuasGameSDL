#include "Input.h"

Input::Input() {
	for (int i = 0; i < MAX_KEYS; i++) {
		keys[i] = false;
	}
}

Input::~Input()	{

}

void Input::setKeyDown(int keyCode)
{
	if (keyCode >= MAX_KEYS) {
		std::cout << "error key too large";
		return;
	}
	keys[keyCode] = true;
}

void Input::setKeyUp(int keyCode)
{
	if (keyCode >= MAX_KEYS) {
		std::cout << "error key too large";
		return;
	}
	keys[keyCode] = false;
}

bool Input::GetKeyDown(int keycode)
{
	return keys[keycode];
}
