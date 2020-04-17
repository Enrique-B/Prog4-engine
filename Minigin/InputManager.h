#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL_scancode.h>

#define MaxNumbersOfControllers 2
class Command;
namespace Fried
{
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

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		bool IsControllerButtonPressed(size_t controllerNumber ,ControllerButton button) const;
		bool IsKeyboardButtonPressed(SDL_Scancode scancode)const;
		void ChangeInput(ControllerButton button1, ControllerButton button2);
		void ChangeInput(SDL_Scancode button1, SDL_Scancode button2);
		void HandleInput();
		void AddCommand(size_t controllerNumber, ControllerButton cb, Command* pCommand);
		void AddCommand(SDL_Scancode cb, Command* pCommand);

	private:
		XINPUT_STATE m_CurrentState[MaxNumbersOfControllers];
		std::vector<std::pair<ControllerButton, Command*>>m_Controller1CommandVector;
		std::vector<std::pair<ControllerButton, Command*>>m_Controller2CommandVector;
		std::vector<std::pair<SDL_Scancode, Command*>>m_KeyboardCommandVector;
	};
}