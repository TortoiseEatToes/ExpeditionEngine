#pragma once

#include <assert.h>
#include "../../Containers/List.h"
#include "Shadow.h"


class ShadowManager
{
public:

	ShadowManager() = default;
	~ShadowManager() = default;

	ShadowManager(ShadowManager&&) = delete;
	ShadowManager(const ShadowManager&) = delete;
	const ShadowManager& operator = (ShadowManager&&) = delete;
	const ShadowManager& operator = (const ShadowManager&) = delete;

	void AddShadow(Shadow* inShadow);
	void RemoveShadow(Shadow* inShadow);

	List<Shadow*>* GetList() 
	{
		return &activeShadowList;
	}

private:
	List<Shadow*> activeShadowList;

};

