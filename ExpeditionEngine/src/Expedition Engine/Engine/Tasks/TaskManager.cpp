#include "TaskManager.h"

#include "../Threads/ThreadManagerAttorney.h"


TaskManager::TaskManager()
{
#if EnableMultiThreading
	SetMultiThreadedMode();
#else
	SetSingleThreadedMode();
#endif
}

TaskManager::~TaskManager()
{
	SanitizeTasks();
}

void TaskManager::ExecuteTasks()
{
#if EnableMultiThreading
	mainLoopStart.Execute();
#else
	singleThreadedList.SetFront(iterator);
	while (!iterator.IsOutOfNodes())
	{
		iterator.GetCurrentObject().Execute();
		++iterator;
	}
#endif
}

void TaskManager::ReportAverageSpeed()
{
	mainLoopStart.ReportAverageSpeed();

	updateFrame.ReportAverageSpeed();

	renderFrameStart.ReportAverageSpeed();
	renderGraphicsObjects.ReportAverageSpeed();
	renderParticles.ReportAverageSpeed();
	renderFrameEnd.ReportAverageSpeed();

	processAudioCommands.ReportAverageSpeed();


	postFrameStart.ReportAverageSpeed();
	synchronizeCurrentScene.ReportAverageSpeed();
	synchronizeCurrentGraphicsScene.ReportAverageSpeed();
	resolveFrame.ReportAverageSpeed();
	postFrameEnd.ReportAverageSpeed();

	mainLoopEnd.ReportAverageSpeed();
}

void TaskManager::PrintTaskParents()
{
	EngineUtilities::Print("\n------------- END TASK PARENTS ---------------\n");
	mainLoopStart.PrintParents();
	EngineUtilities::Print("\n");

	updateFrame.PrintParents();
	EngineUtilities::Print("\n");

	renderFrameStart.PrintParents();
	EngineUtilities::Print("\n");

	renderGraphicsObjects.PrintParents();
	EngineUtilities::Print("\n");

	renderParticles.PrintParents();
	EngineUtilities::Print("\n");

	renderFrameEnd.PrintParents();
	EngineUtilities::Print("\n");

	processAudioCommands.PrintParents();
	EngineUtilities::Print("\n");


	postFrameStart.PrintParents();
	EngineUtilities::Print("\n");

	synchronizeCurrentScene.PrintParents();
	EngineUtilities::Print("\n");

	synchronizeCurrentGraphicsScene.PrintParents();
	EngineUtilities::Print("\n");

	resolveFrame.PrintParents();
	EngineUtilities::Print("\n");

	postFrameEnd.PrintParents();
	EngineUtilities::Print("\n");

	mainLoopEnd.PrintParents();
	EngineUtilities::Print("\n------------- END TASK PARENTS ---------------\n");
}

void TaskManager::PrintTaskChildren()
{
	EngineUtilities::Print("\n------------- START TASK CHILDREN ---------------\n");
	mainLoopStart.PrintChildren();
	EngineUtilities::Print("\n");

	updateFrame.PrintChildren();
	EngineUtilities::Print("\n");

	renderFrameStart.PrintChildren();
	EngineUtilities::Print("\n");

	renderGraphicsObjects.PrintChildren();
	EngineUtilities::Print("\n");

	renderParticles.PrintChildren();
	EngineUtilities::Print("\n");

	renderFrameEnd.PrintChildren();
	EngineUtilities::Print("\n");

	processAudioCommands.PrintChildren();
	EngineUtilities::Print("\n");


	postFrameStart.PrintChildren();
	EngineUtilities::Print("\n");

	synchronizeCurrentScene.PrintChildren();
	EngineUtilities::Print("\n");

	synchronizeCurrentGraphicsScene.PrintChildren();
	EngineUtilities::Print("\n");

	resolveFrame.PrintChildren();
	EngineUtilities::Print("\n");

	postFrameEnd.PrintChildren();
	EngineUtilities::Print("\n");

	mainLoopEnd.PrintChildren();
	EngineUtilities::Print("\n------------- END TASK CHILDREN ---------------\n");
}

void TaskManager::SetSingleThreadedMode()
{
	singleThreadedList.PushBack(&mainLoopStart);

	singleThreadedList.PushBack(&updateFrame);

	singleThreadedList.PushBack(&renderFrameStart);
	singleThreadedList.PushBack(&renderGraphicsObjects);
	singleThreadedList.PushBack(&renderParticles);
	singleThreadedList.PushBack(&renderFrameEnd);

	singleThreadedList.PushBack(&processAudioCommands);

	singleThreadedList.PushBack(&postFrameStart);
	singleThreadedList.PushBack(&resolveFrame);
	singleThreadedList.PushBack(&synchronizeCurrentScene);
	singleThreadedList.PushBack(&synchronizeCurrentGraphicsScene);
	singleThreadedList.PushBack(&postFrameEnd);

	singleThreadedList.PushBack(&mainLoopEnd);
}

void TaskManager::SetMultiThreadedMode()
{
	mainLoopStart.AssignChild(&updateFrame);
	mainLoopStart.AssignChild(&renderFrameStart);
	mainLoopStart.AssignChild(&processAudioCommands);

	updateFrame.AssignChild(&postFrameStart);

	renderFrameStart.AssignChild(&renderGraphicsObjects);
	renderFrameStart.AssignChild(&renderParticles);

	renderGraphicsObjects.AssignChild(&renderFrameEnd);
	renderParticles.AssignChild(&renderFrameEnd);

	renderFrameEnd.AssignChild(&postFrameStart);

	postFrameStart.AssignChild(&resolveFrame);
	postFrameStart.AssignChild(&synchronizeCurrentScene);
	postFrameStart.AssignChild(&synchronizeCurrentGraphicsScene);

	resolveFrame.AssignChild(&postFrameEnd);
	synchronizeCurrentScene.AssignChild(&postFrameEnd);
	synchronizeCurrentGraphicsScene.AssignChild(&postFrameEnd);

	postFrameEnd.AssignChild(&mainLoopEnd);
}

void TaskManager::SanitizeTasks()
{
	mainLoopStart.Sanitize();

	updateFrame.Sanitize();

	renderFrameStart.Sanitize();
	renderGraphicsObjects.Sanitize();
	renderParticles.Sanitize();
	renderFrameEnd.Sanitize();

	processAudioCommands.Sanitize();

	postFrameStart.Sanitize();
	synchronizeCurrentScene.Sanitize();
	synchronizeCurrentGraphicsScene.Sanitize();
	resolveFrame.Sanitize();
	postFrameEnd.Sanitize();

	mainLoopEnd.Sanitize();
}

void TaskManager::PrintTaskFamilyTree()
{
	EngineUtilities::Print("\n----------- START TASK FAMILY TREE ------------\n");
	
	mainLoopStart.PrintParents();
	mainLoopStart.PrintChildren();
	EngineUtilities::Print("\n");

	updateFrame.PrintParents();
	updateFrame.PrintChildren();
	EngineUtilities::Print("\n");

	renderFrameStart.PrintParents();
	renderFrameStart.PrintChildren();
	EngineUtilities::Print("\n");

	renderGraphicsObjects.PrintParents();
	renderGraphicsObjects.PrintChildren();
	EngineUtilities::Print("\n");

	renderParticles.PrintParents();
	renderParticles.PrintChildren();
	EngineUtilities::Print("\n");

	renderFrameEnd.PrintParents();
	renderFrameEnd.PrintChildren();
	EngineUtilities::Print("\n");

	processAudioCommands.PrintParents();
	processAudioCommands.PrintChildren();
	EngineUtilities::Print("\n");


	postFrameStart.PrintParents();
	postFrameStart.PrintChildren();
	EngineUtilities::Print("\n");

	synchronizeCurrentScene.PrintParents();
	synchronizeCurrentScene.PrintChildren();
	EngineUtilities::Print("\n");

	synchronizeCurrentGraphicsScene.PrintParents();
	synchronizeCurrentGraphicsScene.PrintChildren();
	EngineUtilities::Print("\n");

	resolveFrame.PrintParents();
	resolveFrame.PrintChildren();
	EngineUtilities::Print("\n");

	postFrameEnd.PrintParents();
	postFrameEnd.PrintChildren();
	EngineUtilities::Print("\n");

	mainLoopEnd.PrintParents();
	mainLoopEnd.PrintChildren();
	EngineUtilities::Print("\n------------- END TASK FAMILY TREE ---------------\n");
}
