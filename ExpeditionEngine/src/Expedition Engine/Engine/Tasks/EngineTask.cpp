#include "EngineTask.h"

#include "../Threads/ThreadManagerAttorney.h"

#include <mutex>

#include <string>
#include <assert.h>

EngineTask::EngineTask(const char* taskName, const PriorityLevel& taskPriorityLevel)
{
	name = taskName;
	priorityLevel = taskPriorityLevel;
}

bool EngineTask::operator==(const EngineTask & other)
{
	return name == other.GetName();
}

void EngineTask::Execute()
{
	StartTrackingTime();
	Work();
	StopTrackingTime();
	ExecuteChildren();
	OnWorkComplete();
}

void EngineTask::ExecuteAsync()
{
	ResetDependencies();
	ThreadManagerAttorney::EngineTaskControl::ExecuteTask(this);
}

void EngineTask::ReportAverageSpeed()
{
#if IgnoreTrivialSpeedTrackingResults
	if (timeTaken > trivialCutOff)
	{
		EngineUtilities::PrintSpeedTracking("\nAverage Time taken by " + name + ": " + std::to_string(totalTimeTaken / timesExecuted));
	}
#else
	//EngineUtilities::PrintSpeedTracking("\nAverage Time taken by " + name +  ": " + std::to_string(totalTimeTaken / timesExecuted));
#endif //IgnoreTrivialSpeedTrackingResults
}

void EngineTask::AssignChild(EngineTask* pOtherTask)
{
	assert(!childTasks.Contains(pOtherTask)); //Check that the list does not already include the task
	childTasks.PushBack(pOtherTask);
	pOtherTask->AssignParent(this);
}

void EngineTask::AssignParent(EngineTask* pOtherTask)
{
	parentTasks.PushBack(pOtherTask);
	ResetDependencies();
}

void EngineTask::InformParentIsFinished()
{
	//Only submit the task to the work queue if all of it's parents are finished
	if (--dependenciesRemaining == 0)
	{
		ExecuteAsync();
	}
}

void EngineTask::Sanitize()
{
	childTasks.Clear();
	parentTasks.Clear();
	ResetDependencies();
}

void EngineTask::PrintParents()
{
	List<EngineTask*>::Iterator tempIterator;
	parentTasks.SetFront(tempIterator);
	EngineUtilities::Print("\nParents of " + name);
	if (parentTasks.GetSize() > 0)
	{
		while (!tempIterator.IsOutOfNodes())
		{
			EngineUtilities::Print("\n   " + tempIterator.GetCurrentObject()->GetName());
			++tempIterator;
		}
	}
	else
	{
		EngineUtilities::Print("\n   None");
	}
}

void EngineTask::PrintChildren()
{
	List<EngineTask*>::Iterator tempIterator;
	childTasks.SetFront(tempIterator);
	EngineUtilities::Print("\nChildren of " + name);
	if (childTasks.GetSize() > 0)
	{
		while (!tempIterator.IsOutOfNodes())
		{
			EngineUtilities::Print("\n   " + tempIterator.GetCurrentObject()->GetName());
			++tempIterator;
		}
	}
	else
	{
		EngineUtilities::Print("\n   None");
	}
}

void EngineTask::ExecuteChildren()
{
	childTasks.SetFront(iterator);
	while (!iterator.IsOutOfNodes())
	{
		iterator.GetCurrentObject()->InformParentIsFinished();
		++iterator;
	}
}

void EngineTask::ResetDependencies()
{
	dependenciesRemaining = parentTasks.GetSize();
}

void EngineTask::StartTrackingTime()
{
#if EnableEngineThreadSpeedTracking
	stopWatch.Start();
#endif
}

void EngineTask::StopTrackingTime()
{
#if EnableEngineThreadSpeedTracking
	totalTimeTaken += stopWatch.Stop();
	++timesExecuted;
#if IgnoreTrivialSpeedTrackingResults
	if (timeTaken > trivialCutOff)
	{
		EngineUtilities::PrintSpeedTracking("\nTime taken by " + name + " " + std::to_string(stopWatch.GetElapsedTime()));
	}
#else
	EngineUtilities::PrintSpeedTracking("\nTime taken by " + name + " " + std::to_string(stopWatch.GetElapsedTime()));
#endif //IgnoreTrivialSpeedTrackingResults

#endif //EnableEngineThreadSpeedTracking
}
