#pragma once

#include "EngineTask.h"

//This task does literally nothing.  It is only used for when creating new worker threads.  
//This gives them a starting task to execute so they can jump right back into the idle pool afterwards.
class Task_Null : public EngineTask
{
public:
	Task_Null();
	Task_Null(const Task_Null& other) = delete;
	Task_Null& operator= (const Task_Null& other) = delete;
	~Task_Null() = default;

private:
	void Work() override;
};