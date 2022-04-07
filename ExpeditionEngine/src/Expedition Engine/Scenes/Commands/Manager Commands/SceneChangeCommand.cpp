#include "SceneChangeCommand.h"

#include "../../SceneManagerAttorney.h"

void SceneChangeCommand::Execute()
{
	SceneManagerAttorney::ManagerCommandControl::ChangeScene(sceneName);
}