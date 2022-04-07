#include "Forest_Camera.h"
#include "../../Expedition Engine/Scene Components/Input/Manager/InputManager.h"
#include "../../Expedition Engine/DX12App/DXApp/DXApp_12.h"

Forest_Camera::Forest_Camera(SceneName sceneName) : GameObject(sceneName)
{
	currentSpeed = walkSpeed;

	camBack.speed = -currentSpeed;
	camFwd.speed =   currentSpeed;
	camLeft.speed = -currentSpeed;
	camRight.speed = currentSpeed;


	camUpdate.camSpeed = 0.001f;

	SetCursorPos(static_cast<int>(DXApp_12::GetWidth() * 0.5f), static_cast<int>(DXApp_12::GetHeight() * 0.5f));
	camUpdate.prevCamX = static_cast<int>(DXApp_12::GetWidth() * 0.5f);
	camUpdate.prevCamY = static_cast<int>(DXApp_12::GetHeight() * 0.5f);

	inputSprint.walkSpeed = walkSpeed;
	inputSprint.sprintSpeed = sprintSpeed;
	inputSprint.cam = this;
}

Forest_Camera::~Forest_Camera()
{
}

float Forest_Camera::GetSpeed() const
{
	return currentSpeed;
}

void Forest_Camera::SetSpeed(const float& inSpeed)
{
	currentSpeed = inSpeed;

	camBack.speed = -currentSpeed;
	camFwd.speed =   currentSpeed;
	camLeft.speed = -currentSpeed;
	camRight.speed = currentSpeed;
}

void Forest_Camera::SetTerrainAlignInfo(TerrainModel* inTerrain, Camera* cam, const float& offset)
{
	camUpdate.terrain = inTerrain;
	camUpdate.offset = offset;
	camUpdate.cam = cam;
}

void Forest_Camera::OnSceneEnter()
{
	camBack.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyS);
	camFwd.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyW);
	camLeft.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyA);
	camRight.RegisterForOnHeld(GetRegisteredScene(), Input::LetterKeyD);

	inputSprint.RegisterForOnPressed(GetRegisteredScene(), Input::ShiftLeft);
	inputSprint.RegisterForOnReleased(GetRegisteredScene(), Input::ShiftLeft);

	inputFlash.RegisterForOnPressed(GetRegisteredScene(), Input::LetterKeyE);
	inputFlash.RegisterForOnReleased(GetRegisteredScene(), Input::LetterKeyE);

	camUpdate.StartUpdating(GetRegisteredScene());
}

void Forest_Camera::OnSceneExit()
{
	camBack.DeregisterFromOnHeld();
	camFwd.DeregisterFromOnHeld();
	camLeft.DeregisterFromOnHeld();
	camRight.DeregisterFromOnHeld();

	inputSprint.DeregisterFromOnPressed();
	inputSprint.DeregisterFromOnReleased();

	inputFlash.DeregisterFromOnPressed();
	inputFlash.DeregisterFromOnReleased();

	camUpdate.StopUpdating();
}
