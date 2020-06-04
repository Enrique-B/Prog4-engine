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
	Input(Command* pCom, inputState inputState, SDL_Scancode scan, size_t controllerNum, ControllerButton controllerbut)noexcept(false);
	Input(Command* pCom, inputState inputState, SDL_Scancode scan)noexcept(false);
	Input(Command* pCom, inputState inputState, size_t controllerNum, ControllerButton controllerbut)noexcept(false);
};

namespace Fried
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput()noexcept;
		bool IsControllerButtonPressed(const size_t controllerNumber ,ControllerButton button) const noexcept;
		bool IsKeyboardButtonPressed(SDL_Scancode scancode)const noexcept;
		void AddCommand(const Input& input) noexcept(false);
		void HandleInput();
	private:
		XINPUT_STATE m_CurrentState[MaxNumbersOfControllers];
		std::vector<Input> m_CommandVector;
	};
}