#include "InputManager.h"
#include "include.h"


void InputManager::CheckKey()
{
	//Sleep(50);
	inputKey = 0x00000000;
	if (GetAsyncKeyState(VK_UP))
		inputKey |= KEYID_UP;
	if (GetAsyncKeyState(VK_DOWN))
		inputKey |= KEYID_DOWN;
	if (GetAsyncKeyState(VK_LEFT))
		inputKey |= KEYID_LEFT;
	if (GetAsyncKeyState(VK_RIGHT))
		inputKey |= KEYID_RIGHT;
	if (GetAsyncKeyState(VK_RETURN))
		inputKey |= KEYID_RETURN;
	if (GetAsyncKeyState(VK_SPACE))
		inputKey |= KEYID_SPACE;
	if (GetAsyncKeyState(VK_ESCAPE))
		inputKey |= KEYID_ESCAPE;
	if (GetAsyncKeyState(VK_CONTROL))
		inputKey |= KEYID_CONTROL;
}

InputManager::InputManager() : inputKey()
{
}

InputManager::~InputManager()
{
}

