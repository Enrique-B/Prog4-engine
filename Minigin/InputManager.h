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
	pressed = 1,
	down = 2
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
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;
		~InputManager();

		bool ProcessInput()noexcept;
		bool IsControllerButtonPressed(const size_t controllerNumber ,ControllerButton button) const noexcept;
		bool IsKeyboardButtonPressed(SDL_Scancode scancode)const noexcept;
		void AddCommand(const Input& input) noexcept(false);
		void HandleInput()noexcept;
		void RemoveAllCommands()noexcept;
	private:
		friend class Singleton<InputManager>;
		InputManager() = default;
		XINPUT_STATE m_CurrentState[MaxNumbersOfControllers]{};
		std::vector<Input> m_CommandVector;
		const Uint8* keyboardState{};
	};
}