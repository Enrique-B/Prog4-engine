#include "MiniginPCH.h"
#include "InputManager.h"
#include "Command.h"
#include <SDL.h>
#include <ostream>

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

InputManager::~InputManager()
{
	size_t size{ m_ControllerCommandVector.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_ControllerCommandVector[i].second);
	}
	size = m_KeyboardCommandVector.size();
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_KeyboardCommandVector[i].second);
	}
}

bool InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);
	SDL_Event e{};
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
	}
	return true;
}

bool InputManager::IsControllerButtonPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DPadDown:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DPadUp:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DPadRight:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::DPadLeft:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::StartButton:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case ControllerButton::RightTrigger:
		return m_CurrentState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	case ControllerButton::LeftTrigger:
		return m_CurrentState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	case ControllerButton::RightBumper:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ControllerButton::LeftBumbper:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	default: return false;
	}
}

bool InputManager::IsKeyboardButtonPressed(SDL_Scancode scancode) const
{
	SDL_Event e{};
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			return (e.key.keysym.scancode == scancode);
		}
	}
	return false;
}

void InputManager::HandleInput()
{
	ProcessInput();
	size_t size{ m_ControllerCommandVector.size() };
	for (size_t i = 0; i < size; i++)
	{
		if (IsControllerButtonPressed(m_ControllerCommandVector[i].first))
		{
			m_ControllerCommandVector[i].second->Execute();
		}
	}
	size = m_KeyboardCommandVector.size();
	for (size_t i = 0; i < size; i++)
	{
		if (IsKeyboardButtonPressed(m_KeyboardCommandVector[i].first))
		{
			m_KeyboardCommandVector[i].second->Execute();
		}
	}
}

void InputManager::AddCommand(ControllerButton cb, Command* pCommand)
{
	const size_t size{ m_ControllerCommandVector.size() };
	for (size_t i = 0; i < size; i++)
	{
		if (m_ControllerCommandVector[i].first == cb)
		{
			std::cout << "controllerButton is already in use " << cb << std::endl;
		}
	}
	m_ControllerCommandVector.push_back(std::make_pair(cb, pCommand));
}

void InputManager::AddCommand(SDL_Scancode sc, Command* pCommand)
{
	m_KeyboardCommandVector.push_back(std::make_pair(sc, pCommand));
}
