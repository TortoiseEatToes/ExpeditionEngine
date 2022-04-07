#pragma once

#include "Task_MainLoopStart.h"

#include "Task_UpdateFrame.h"

#include "Task_RenderFrameStart.h"
#include "Task_RenderGraphicsObjects.h"
#include "Task_RenderParticles.h"
#include "Task_RenderFrameEnd.h"

#include "Task_ProcessAudioCommands.h"

#include "Task_PostFrameStart.h"
#include "Task_SynchronizeCurrentScene.h"
#include "Task_SynchronizeCurrentGraphicsScene.h"
#include "Task_ResolveFrame.h"
#include "Task_PostFrameEnd.h"

#include "Task_MainLoopEnd.h"

#include "../../Containers/List.h"

//This manager owns all of the task objects and manages the task graph that the ExpeditionEngine singleton will execute.
class TaskManager
{
public:
	TaskManager();
	TaskManager(const TaskManager& other) = delete;
	TaskManager& operator= (const TaskManager& other) = delete;
	~TaskManager();

	/// <summary>Call execute on the root task.  This will kick off the rest of the graph starting with the concurrent and then the consecutive tasks of the root task.</summary>
	void ExecuteTasks();

	/// <summary>Tell all of the tasks to report the average amount of time it took for them to complete.</summary>
	void ReportAverageSpeed();

	/// <summary>Call sanitize on all of the tasks.</summary>
	void SanitizeTasks();

	void PrintTaskFamilyTree();

	void PrintTaskParents();

	void PrintTaskChildren();

private:
	/// <summary>Set up the task graph to only use consecutive tasks.</summary>
	void SetSingleThreadedMode();

	/// <summary>Set up the task graph to use concurrency.</summary>
	void SetMultiThreadedMode();

	List<EngineTask*> singleThreadedList;
	List<EngineTask*>::Iterator iterator;

	Task_MainLoopStart mainLoopStart;

	Task_UpdateFrame updateFrame;

	Task_RenderFrameStart renderFrameStart;
	Task_RenderGraphicsObjects renderGraphicsObjects;
	Task_RenderParticles renderParticles;
	Task_RenderFrameEnd renderFrameEnd;

	Task_ProcessAudioCommands processAudioCommands;


	Task_PostFrameStart postFrameStart;
	Task_SynchronizeCurrentScene synchronizeCurrentScene;
	Task_SynchronizeCurrentGraphicsScene synchronizeCurrentGraphicsScene;
	Task_ResolveFrame resolveFrame;
	Task_PostFrameEnd postFrameEnd;

	Task_MainLoopEnd mainLoopEnd;
};