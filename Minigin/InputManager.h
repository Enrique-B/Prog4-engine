#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <SDL_keycode.h>
#include <XInput.h>

#define MaxNumbersOfControllers 2
class Command;
enum class ControllerButton
{
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	//DPad Buttons  
	DPadUp,
	DPadDown,
	DPadRight,
	DPadLeft,
	StartButton,
	// triggers
	RightTrigger,
	LeftTrigger,
	// bumpers
	RightBumper,
	LeftBumbper
};

enum class inputState
{
	release = 0, 
	pressed = 1
};

struct Input
{
	size_t controllerNumber;
	ControllerButton button; 
	SDL_Scancode keyboardKey;
	Command* pCommand; 
	inputState state;
	bool useController; 
	bool useKeyboard;
	bool wasButtonPressedLastFrame; 
	bool wasKeyPressedLastFrame;
	Input(Command* pC, inputState st, SDL_Scancode scan, size_t cn, ControllerButton cb);
	Input(Command* pC, inputState st, SDL_Scancode scan);
	Input(Command* pC, inputState st, size_t cn, ControllerButton cb);
};

namespace Fried
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		bool IsControllerButtonPressed(const size_t controllerNumber ,ControllerButton button) const;
		bool IsKeyboardButtonPressed(SDL_Scancode scancode)const;
		void AddCommand(const Input& input);
		void HandleInput();
	private:
		XINPUT_STATE m_CurrentState[MaxNumbersOfControllers];
		std::vector<Input> m_CommandVector;
	};
}