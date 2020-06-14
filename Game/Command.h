#pragma once
class Audio;
class GameObject;
class Command
{
public: 
	Command(GameObject* pObject);
	Command(const Command& other) = delete;
	Command(Command&& other) = delete;
	Command& operator=(const Command& other) = delete;
	Command& operator=(Command&& other) = delete;
	virtual ~Command() = default;
	virtual void Execute() = 0;
protected: 
	GameObject* m_pObject;
};

class JumpCommand : public Command
{
public:
	JumpCommand(GameObject* pObject);
	JumpCommand(const JumpCommand& other) = delete;
	JumpCommand(JumpCommand&& other) = delete;
	JumpCommand& operator=(const JumpCommand& other) = delete;
	JumpCommand& operator=(JumpCommand&& other) = delete;
	~JumpCommand() = default;

	void Execute();
};

class MoveLeftCommand : public Command
{
public:
	MoveLeftCommand(GameObject* pObject);
	MoveLeftCommand(const MoveLeftCommand& other) = delete;
	MoveLeftCommand(MoveLeftCommand&& other) = delete;
	MoveLeftCommand& operator=(const MoveLeftCommand& other) = delete;
	MoveLeftCommand& operator=(MoveLeftCommand&& other) = delete;
	~MoveLeftCommand() = default;
	void Execute();
};

class ReleaseMovementCommand : public Command
{
public:
	ReleaseMovementCommand(GameObject* pObject);
	ReleaseMovementCommand(const ReleaseMovementCommand& other) = delete;
	ReleaseMovementCommand(ReleaseMovementCommand&& other) = delete;
	ReleaseMovementCommand& operator=(const ReleaseMovementCommand& other) = delete;
	ReleaseMovementCommand& operator=(ReleaseMovementCommand&& other) = delete;
	~ReleaseMovementCommand() = default;
	void Execute();
};

class MoveRightCommand : public Command
{
public:
	MoveRightCommand(GameObject* pObject);
	MoveRightCommand(const MoveRightCommand& other) = delete;
	MoveRightCommand(MoveRightCommand&& other) = delete;
	MoveRightCommand& operator=(const MoveRightCommand& other) = delete;
	MoveRightCommand& operator=(MoveRightCommand&& other) = delete;
	~MoveRightCommand() = default;

	void Execute();
};

class ShootBubbleCommand : public Command
{
public:
	ShootBubbleCommand(GameObject* pObject);
	ShootBubbleCommand(const ShootBubbleCommand& other) = delete;
	ShootBubbleCommand(ShootBubbleCommand&& other) = delete;
	ShootBubbleCommand& operator=(const ShootBubbleCommand& other) = delete;
	ShootBubbleCommand& operator=(ShootBubbleCommand&& other) = delete;
	~ShootBubbleCommand() = default;

	void Execute();
};

class ChangeSceneCommand : public Command
{
public: 
	ChangeSceneCommand();
	ChangeSceneCommand(const ChangeSceneCommand& other) = delete;
	ChangeSceneCommand(ChangeSceneCommand&& other) = delete;
	ChangeSceneCommand& operator=(const ChangeSceneCommand& other) = delete;
	ChangeSceneCommand& operator=(ChangeSceneCommand&& other) = delete;
	~ChangeSceneCommand() = default;

	void Execute();
};

class DebugRenderCommand : public Command
{
public:
	DebugRenderCommand() : Command(nullptr) {};
	DebugRenderCommand(const DebugRenderCommand& other) = delete;
	DebugRenderCommand(DebugRenderCommand&& other) = delete;
	DebugRenderCommand& operator=(const DebugRenderCommand& other) = delete;
	DebugRenderCommand& operator=(DebugRenderCommand&& other) = delete;
	~DebugRenderCommand() = default;

	void Execute();
};

class PauseCommand : public Command
{
public:
	PauseCommand() : Command(nullptr) {};
	PauseCommand(const PauseCommand& other) = delete;
	PauseCommand(PauseCommand&& other) = delete;
	PauseCommand& operator=(const PauseCommand& other) = delete;
	PauseCommand& operator=(PauseCommand&& other) = delete;
	~PauseCommand() = default;

	void Execute();
};