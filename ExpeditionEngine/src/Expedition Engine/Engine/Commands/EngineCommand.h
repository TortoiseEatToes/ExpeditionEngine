#ifndef EXPEDITIONENGINECOMMAND_H
#define EXPEDITIONENGINECOMMAND_H

class EngineCommand
{
public:
	EngineCommand() = default;
	EngineCommand(const EngineCommand&) = delete;
	EngineCommand& operator= (const EngineCommand&) = delete;
	~EngineCommand() = default;

	virtual void Execute() = 0;
};

#endif // !EXPEDITIONENGINECOMMAND_H