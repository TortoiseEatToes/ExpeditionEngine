#include "Update_Camera.h"

#include "../../Expedition Engine/Camera/Camera.h"
#include "../../Expedition Engine/Graphics/Terrain/TerrainModel.h"
#include "../../Expedition Engine/Scene Components/Input/Manager/InputManager.h"
#include "../../Expedition Engine/DX12App/DXApp/DXApp_12.h"

void Update_Camera::OnUpdate()
{
	if (GetForegroundWindow() == DXApp_12::GetWindow())
	{
		cam->AlignHeightToTerrain(terrain, offset);

		cam->Update();

		WINDOWPLACEMENT* wndPlace = new WINDOWPLACEMENT();

		GetWindowPlacement(DXApp_12::GetWindow(), wndPlace);

		LPPOINT point = new tagPOINT();

		GetCursorPos(point);

		int deltaX = prevCamX - point->x;
		int deltaY = prevCamY - point->y;

		cam->TurnLeftRight(deltaX * camSpeed);
		cam->TiltUpDown(deltaY * camSpeed);

		prevCamX = point->x;
		prevCamY = point->y;



		if (prevCamX >= wndPlace->rcNormalPosition.right - 10)
		{
			prevCamX = wndPlace->rcNormalPosition.left + 11;
		}
		else if (prevCamX <= wndPlace->rcNormalPosition.left + 10)
		{
			prevCamX = wndPlace->rcNormalPosition.right - 11;
		}

		if (prevCamY >= wndPlace->rcNormalPosition.bottom - 10)
		{
			prevCamY = wndPlace->rcNormalPosition.top + 11;
		}
		else if (prevCamY <= wndPlace->rcNormalPosition.top + 10)
		{
			prevCamY = wndPlace->rcNormalPosition.bottom - 11;
		}

		SetCursorPos(prevCamX, prevCamY);

		delete wndPlace;
		delete point;
	}

}
