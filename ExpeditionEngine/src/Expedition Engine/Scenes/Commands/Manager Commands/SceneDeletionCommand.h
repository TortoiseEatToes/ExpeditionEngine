#pragma once

#include "SceneManagerCommand.h"

class SceneDeletionCommand : public SceneManagerCommand
{
public:
	SceneDeletionCommand() = default;
	SceneDeletionCommand(const SceneDeletionCommand& other) = delete;
	SceneDeletionCommand& operator= (const SceneDeletionCommand& other) = delete;
	virtual ~SceneDeletionCommand() = default;

	void Execute() override;
private:

};