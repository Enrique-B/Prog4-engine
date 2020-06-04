#include "MiniginPCH.h"
#include "InputManager.h"
#include "../../Game/Command.h"
#include <SDL.h>
#include <ostream>

Input::Input(Command* pCom, inputState inputState, SDL_Scancode scan, size_t controllerNum, ControllerButton controllerbut)
{
	if (pCommand == nullptr)
	{
		throw std::runtime_error(std::string("pCommand was nullptr"));
	}
	pCommand = pCom;
	state = inputState;
	keyboardKey = scan;
	useKeyboard = true;
	if (controllerNum < MaxNumbersOfControllers)
	{
		useController = true;
		controllerNumber = controllerNum;
		button = controllerbut;
	}
	else
	{
		useController = false;
		controllerNumber = 3;
		button = controllerbut;
	}
	wasButtonPressedLastFrame = false;
	wasKeyPressedLastFrame = false;
}
Input::Input(Command* pCom, inputState inputState, SDL_Scancode scan)
{
	if (pCommand == nullptr)
	{
		throw std::runtime_error(std::string("pCommand was nullptr"));
	}
	pCommand = pCom;
	state = inputState;
	keyboardKey = scan;
	useKeyboard = true;
	useController = false;
	controllerNumber = 3; 
	button = ControllerButton::StartButton;
	wasButtonPressedLastFrame = false;
	wasKeyPressedLastFrame = false;
}

Input::Input(Command* pCom, inputState inputState, size_t controllerNum, ControllerButton controllerbut)
{
	if (pCommand == nullptr)
	{
		throw std::runtime_error(std::string("pCommand was nullptr"));
	}
	pCommand = pCom;
	state = inputState;
	useKeyboard = false;
	if (controllerNum < MaxNumbersOfControllers)
	{
		useController = true;
		controllerNumber = controllerNum;
		button = controllerbut;
	}
	else
	{
		useController = false;
		controllerNumber = 3;
		button = controllerbut;
	}
	wasButtonPressedLastFrame = false;
	wasKeyPressedLastFrame = false;
	keyboardKey = SDL_Scancode(-1);
}

// just a debug thingy 
std::ostream& operator<<(std::ostream& os, const ControllerButton& cb)
{
	switch (cb)
	{
	case ControllerButton::ButtonA:
		os << "ButtonA";
		break;
	case ControllerButton::ButtonB:
		os << "ButtonB";
		break;
	case ControllerButton::ButtonX:
		os << "ButtonX";
		break;
	case ControllerButton::ButtonY:
		os << "ButtonY";
		break;
	case ControllerButton::DPadUp:
		os << "DPadUp";
		break;
	case ControllerButton::DPadDown:
		os << "DPadDown";
		break;
	case ControllerButton::DPadRight:
		os << "DPadRight";
		break;
	case ControllerButton::DPadLeft:
		os << "DPadLeft";
		break;
	case ControllerButton::StartButton:
		os << "StartButton";
		break;
	case ControllerButton::RightTrigger:
		os << "RightTrigger";
		break;
	case ControllerButton::LeftTrigger:
		os << "LeftTrigger";
		break;
	case ControllerButton::RightBumper:
		os << "RightBumper";
		break;
	case ControllerButton::LeftBumbper:
		os << "LeftBumbper";
		break;
	default:
		break;
	}		
	return os;
}

Fried::InputManager::~InputManager()
{
	const size_t size{ m_CommandVector.size() };
	for (size_t i = 0; i < size; i++)
		SafeDelete(m_CommandVector[i].pCommand);
}

bool Fried::InputManager::ProcessInput()noexcept
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	for (size_t i = 0; i < MaxNumbersOfControllers; i++)
		XInputGetState(0, &m_CurrentState[i]);
	SDL_Event e{};
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			return false;
	}
	return true;
}

bool Fried::InputManager::IsControllerButtonPressed(size_t controllerNumber, ControllerButton button) const noexcept
{
	switch (button)
	{
	case ControllerButton::ButtonA: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DPadDown: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DPadUp: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DPadRight: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::DPadLeft: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::StartButton: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case ControllerButton::RightTrigger: return m_CurrentState[controllerNumber].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	case ControllerButton::LeftTrigger: return m_CurrentState[controllerNumber].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	case ControllerButton::RightBumper: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ControllerButton::LeftBumbper: return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	default: return false;
	}
}

bool Fried::InputManager::IsKeyboardButtonPressed(SDL_Scancode scancode) const noexcept
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	return keyboardState[scancode];
}

void Fried::InputManager::AddCommand(const Input& input)
{
	if (!input.useController && !input.useKeyboard)
	{
		throw std::runtime_error(std::string("input useController and keyboard was false"));
	}
	m_CommandVector.push_back(input);
}

void Fried::InputManager::HandleInput()
{
	ProcessInput();
	const size_t size{m_CommandVector.size()};
	for (size_t i = 0; i < size; i++)
	{
		if (m_CommandVector[i].useKeyboard)
		{
			if (IsKeyboardButtonPressed(m_CommandVector[i].keyboardKey))
			{
				m_CommandVector[i].wasKeyPressedLastFrame = true;
				if (m_CommandVector[i].state == inputState::pressed)
				{
					m_CommandVector[i].pCommand->Execute();
				}
			}
			else if (m_CommandVector[i].wasKeyPressedLastFrame && m_CommandVector[i].state == inputState::release)
			{
				m_CommandVector[i].wasKeyPressedLastFrame = false; 
				m_CommandVector[i].pCommand->Execute();
			}
		}
		if (m_CommandVector[i].useController)
		{
			if (IsControllerButtonPressed(m_CommandVector[i].controllerNumber, m_CommandVector[i].button))
			{
				m_CommandVector[i].wasButtonPressedLastFrame = true;
				if (m_CommandVector[i].state == inputState::pressed)
				{
					m_CommandVector[i].pCommand->Execute();
				}
			}
			else if (m_CommandVector[i].wasButtonPressedLastFrame && m_CommandVector[i].state == inputState::release)
			{
				m_CommandVector[i].wasButtonPressedLastFrame = false;
				m_CommandVector[i].pCommand->Execute();
			}
		}
	}
}