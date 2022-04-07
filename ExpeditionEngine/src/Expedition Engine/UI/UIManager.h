#pragma once

class UIScreen;

class UIManager
{
public:


private:
	friend class UIManagerAttorney;

	static void Initialize()
	{
		pInstance = new UIManager();
	}

	static UIManager& Instance()
	{
		return *pInstance;
	}

	static void Terminate()
	{
		delete pInstance;
	}

	UIManager();
	UIManager(const UIManager& other) = delete;
	UIManager& operator= (const UIManager& other) = delete;
	~UIManager();

	static UIManager* pInstance;

	static void DrawUI()
	{
		Instance().privDrawUI();
	}
	void privDrawUI();


	UIScreen* pCurrentScreen;
};