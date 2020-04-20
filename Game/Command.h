#pragma once
class Audio;
class GameObject;
class Command
{
public: 
	Command(GameObject* pObject);
	virtual ~Command() = default; 
	virtual void Execute() = 0;
protected: 
	GameObject* m_pObject;
};

class JumpCommand : public Command
{
public:
	JumpCommand(GameObject* pObject);
	void Execute();
};

class ChangeSceneCommand : public Command
{
public: 
	ChangeSceneCommand();
	void Execute();
};

class SwapWeapon : public Command
{
public: 
	SwapWeapon(GameObject* pObject);
	void Execute();
};

class Crouch : public Command
{
public:
	Crouch(GameObject* pObject);
	void Execute();
};

class PlaceholderDPadUpCommand : public Command
{
public:
	void Execute();
};

class PlaceholderDPadDownCommand : public Command
{
public:
	void Execute();
};

class PlaceholderDPadRightCommand : public Command
{
public:
	void Execute();
};

class PlaceholderDPadLeftCommand : public Command
{
public:
	void Execute();
};

class PauseCommand : public Command
{
public: 
	void Execute();
};

class PlaceHolderRightTrigger : public Command
{
public: 
	void Execute();
};

class PlaceHolderLeftTrigger : public Command
{
public: 
	void Execute();
};

class PlaceHolderRightBumper : public Command
{
public: 
	void Execute();
};

class PlaceHolderLeftBumper : public Command
{
public:
	void Execute();
};