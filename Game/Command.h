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

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(GameObject* pObject);
	void Execute();
};

class ReleaseMovementCommand : public Command
{
public:
	ReleaseMovementCommand(GameObject* pObject);
	void Execute();
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(GameObject* pObject);
	void Execute();
};

class ShootBubbleCommand : public Command
{
public:
	ShootBubbleCommand(GameObject* pObject);
	void Execute();
};

class ChangeSceneCommand : public Command
{
public: 
	ChangeSceneCommand();
	void Execute();
};

class DebugRenderCommand : public Command
{
public:
	DebugRenderCommand() : Command(nullptr) {};
	void Execute();
};