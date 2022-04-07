#pragma once

#include "SceneManagerCommand.h"

class SceneChangeCommand : public SceneManagerCommand
{
public:
	SceneChangeCommand() = default;
	SceneChangeCommand(const SceneChangeCommand& other) = delete;
	SceneChangeCommand& operator= (const SceneChangeCommand& other) = delete;
	virtual ~SceneChangeCommand() = default;


	void Execute() override;
private:

};