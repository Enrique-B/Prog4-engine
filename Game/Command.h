#pragma once
class Audio;
struct GameActor;
class Command
{
public: 
	virtual ~Command() = default; 
	virtual void Execute() = 0;
};

class JumpCommand : public Command
{
public:
	void Execute();
};

class FireCommand : public Command
{
public: 
	void Execute();
};

class SwapWeapon : public Command
{
public: 
	void Execute();
};

class Crouch : public Command
{
public:
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