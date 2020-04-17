#include "MiniginPCH.h"
#include "InputManager.h"
#include "../../Game/Command.h"
#include <SDL.h>
#include <ostream>

// just a debug thingy 
std::ostream& operator<<(std::ostream& os, const Fried::ControllerButton& cb)
{
	switch (cb)
	{
	case Fried::ControllerButton::ButtonA:
		os << "ButtonA";
		break;
	case Fried::ControllerButton::ButtonB:
		os << "ButtonB";
		break;
	case Fried::ControllerButton::ButtonX:
		os << "ButtonX";
		break;
	case Fried::ControllerButton::ButtonY:
		os << "ButtonY";
		break;
	case Fried::ControllerButton::DPadUp:
		os << "DPadUp";
		break;
	case Fried::ControllerButton::DPadDown:
		os << "DPadDown";
		break;
	case Fried::ControllerButton::DPadRight:
		os << "DPadRight";
		break;
	case Fried::ControllerButton::DPadLeft:
		os << "DPadLeft";
		break;
	case Fried::ControllerButton::StartButton:
		os << "StartButton";
		break;
	case Fried::ControllerButton::RightTrigger:
		os << "RightTrigger";
		break;
	case Fried::ControllerButton::LeftTrigger:
		os << "LeftTrigger";
		break;
	case Fried::ControllerButton::RightBumper:
		os << "RightBumper";
		break;
	case Fried::ControllerButton::LeftBumbper:
		os << "LeftBumbper";
		break;
	default:
		break;
	}		
	return os;
}

Fried::InputManager::~InputManager()
{
	size_t size{ m_Controller1CommandVector.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_Controller1CommandVector[i].second);
	}
	size = m_KeyboardCommandVector.size();
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_KeyboardCommandVector[i].second);
	}
}

bool Fried::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	for (size_t i = 0; i < MaxNumbersOfControllers; i++)
	{
		XInputGetState(0, &m_CurrentState[i]);
	}
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

bool Fried::InputManager::IsControllerButtonPressed(size_t controllerNumber, Fried::ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DPadDown:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::DPadUp:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DPadRight:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::DPadLeft:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::StartButton:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case ControllerButton::RightTrigger:
		return m_CurrentState[controllerNumber].Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	case ControllerButton::LeftTrigger:
		return m_CurrentState[controllerNumber].Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
	case ControllerButton::RightBumper:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ControllerButton::LeftBumbper:
		return m_CurrentState[controllerNumber].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	default: return false;
	}
}

bool Fried::InputManager::IsKeyboardButtonPressed(SDL_Scancode scancode) const
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

void Fried::InputManager::HandleInput()
{
	ProcessInput();
	size_t size{ m_Controller1CommandVector.size() };
	for (size_t i = 0; i < size; i++)
	{
		if (IsControllerButtonPressed(0,m_Controller1CommandVector[i].first))
		{
			m_Controller1CommandVector[i].second->Execute();
		}
	}
	size = m_Controller2CommandVector.size();
	for (size_t i = 0; i < size; i++)
	{
		if (IsControllerButtonPressed(1, m_Controller2CommandVector[i].first))
		{
			m_Controller2CommandVector[i].second->Execute();
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

void Fried::InputManager::AddCommand(size_t controllerNumber, ControllerButton cb, Command* pCommand)
{
	if (controllerNumber == 0)
	{
		const size_t size{ m_Controller1CommandVector.size() };
		for (size_t i = 0; i < size; i++)
		{
			if (m_Controller1CommandVector[i].first == cb)
			{
				std::cout << "controllerButton is already in use " << cb << std::endl;
			}
		}
		m_Controller1CommandVector.push_back(std::make_pair(cb, pCommand));
	}
	else if (controllerNumber == 1)
	{
		const size_t size{ m_Controller2CommandVector.size() };
		for (size_t i = 0; i < size; i++)
		{
			if (m_Controller2CommandVector[i].first == cb)
			{
				std::cout << "controllerButton is already in use " << cb << std::endl;
			}
		}
		m_Controller2CommandVector.push_back(std::make_pair(cb, pCommand));
	}
	
}

void Fried::InputManager::AddCommand(SDL_Scancode sc, Command* pCommand)
{
	const size_t size{ m_KeyboardCommandVector.size() };
	for (size_t i = 0; i < size; i++)
	{
		if (m_KeyboardCommandVector[i].first == sc)
		{
			std::cout << "controllerButton is already in use " << sc << std::endl;
		}
	}
	m_KeyboardCommandVector.push_back(std::make_pair(sc, pCommand));
}