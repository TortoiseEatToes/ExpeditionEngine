#pragma once

#include "../Scene Components/Input/Mouse/MouseInputComponent.h"

class ButtonManager;

class MouseLeftButtonTracker : public MouseInputComponent
{
public:
	MouseLeftButtonTracker() = delete;
	MouseLeftButtonTracker(ButtonManager* buttonManager);
	MouseLeftButtonTracker(const MouseLeftButtonTracker& other) = delete;
	MouseLeftButtonTracker& operator= (const MouseLeftButtonTracker& other) = delete;
	~MouseLeftButtonTracker() = default;

	void OnPressed() override;
	void OnHeld() override;
	void OnReleased() override;

	void SetButtonManager(ButtonManager* const& buttonManager);

private:
	ButtonManager* pButtonManager;
};