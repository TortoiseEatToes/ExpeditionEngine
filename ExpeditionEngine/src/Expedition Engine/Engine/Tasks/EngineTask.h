#pragma once

#include "../../Containers/List.h"

#include "../EngineUtilities.h"

#include "../../../Expedition Resources/EngineSettings.h"

#if EnableEngineThreadSpeedTracking
#include "../../Time/StopwatchFloat.h"
#endif

#include <condition_variable>
#include <atomic>


//This is the parent class that all of our engine tasks inherit from.  These children will form the task graph that our engine will execute.
class EngineTask
{
public:
	enum PriorityLevel
	{
		High = 3,
		Medium = 2,
		Low = 1
	};

	EngineTask() = delete;
	EngineTask(const char* taskName, const PriorityLevel& taskPriorityLevel);
	EngineTask(const EngineTask& other) = delete;
	EngineTask& operator= (const EngineTask& other) = delete;
	bool operator == (const EngineTask& other);
	~EngineTask() = default;

	///<summary>This is called by the task manager or WorkerThreads to do the work inside this task.</summary>
	void Execute();

	///<summary>Call this function to have this task be done by another thread.</summary>
	void ExecuteAsync();

	///<summary>Print the average time that it took for this task to complete it's work function.</summary>
	void ReportAverageSpeed();

	///<summary>Assign a child task to this task. This will mark that other task as being dependent on this one.</summary>
	void AssignChild(EngineTask* pOtherTask);

	const PriorityLevel& GetPriorityLevel() const { return priorityLevel; }
	const std::string& GetName() const { return name; }


	///<summary>Wipe all data contained in this task.</summary>
	void Sanitize();

	///<summary>Print the names of every parent.</summary>
	void PrintParents();

	///<summary>Print the names of every child.</summary>
	void PrintChildren();

protected:
	///<summary>Override this to define what the worker thread should do.</summary>
	virtual void Work() = 0;

	///<summary>Override this to know when the worker thread is completed with all of it's work.  This is useful for cases where you want to reuse tasks.</summary>
	virtual void OnWorkComplete() {};

private:
	///<summary>Send this task to the thread queue.</summary>
	void InformParentIsFinished();

	void ExecuteChildren();
	void ResetDependencies();

	void StartTrackingTime();
	void StopTrackingTime();

	void AssignParent(EngineTask* pOtherTask);

	List<EngineTask*> parentTasks;
	List<EngineTask*> childTasks;
	List<EngineTask*>::Iterator iterator;
	std::string name;
	std::atomic<int> dependenciesRemaining = 0;
	PriorityLevel priorityLevel;

#if EnableEngineThreadSpeedTracking
	StopwatchFloat stopWatch;
	float timesExecuted = 0.0f;
	float totalTimeTaken = 0.0f;
	const float trivialCutOff = 0.00001f;
#endif
};