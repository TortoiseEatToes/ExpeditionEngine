#include "Task_Null.h"

Task_Null::Task_Null()
	: EngineTask("Null", EngineTask::PriorityLevel::Low)
{
	//Do nothing
}

void Task_Null::Work()
{
	//Do nothing
}
