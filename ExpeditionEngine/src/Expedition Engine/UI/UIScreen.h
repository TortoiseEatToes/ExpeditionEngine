#pragma once

class UILayer;

class UIScreen
{
public:
	UIScreen() = default;
	UIScreen(const UIScreen& other) = delete;
	UIScreen& operator= (const UIScreen& other) = delete;
	~UIScreen() = default;

	void Draw();

private:

	UILayer* pActiveLayer;


};