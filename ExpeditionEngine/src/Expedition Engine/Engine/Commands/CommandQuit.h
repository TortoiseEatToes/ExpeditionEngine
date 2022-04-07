#ifndef COMMANDQUITGAME_H
#define COMMANDQUITGAME_H

#include "EngineCommand.h"

class CommandQuit : public EngineCommand
{
public:
	CommandQuit() = default;
	CommandQuit(const CommandQuit&) = delete;
	CommandQuit& operator= (const CommandQuit&) = delete;
	~CommandQuit() = default;

	virtual void Execute();
};

#endif // !COMMANDQUIT_H

