#include "RandomColorAlarm.h"

#include "../../Expedition Engine/Graphics/GraphicsObjects/GraphicsObject_Color.h"

#include "../../Expedition Engine/Math/Vector/Vector4F.h"

void RandomColorAlarm::OnAlarm()
{
	float randomNumber1 = static_cast <float> (rand()) / 255.0f;
	float randomNumber2 = static_cast <float> (rand()) / 255.0f;
	float randomNumber3 = static_cast <float> (rand()) / 255.0f;
	testInstance->SetColor(Vector4F(randomNumber1 / 255.0f, randomNumber2 / 255.0f, randomNumber3 / 255.0f, 1.0f));
	SetAlarm(registeredScene, timeBetweenAlarms);
}