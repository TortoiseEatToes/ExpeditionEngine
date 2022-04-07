#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H

#if _DEBUG

//Use these to test the engine
#define EnableMultiThreading true
#define EnableEngineThreadSpeedTracking true
#define IgnoreTrivialSpeedTrackingResults false
#define EnableEngineThreadDebugLog false
#define EnableWarningLog false
#define PrintDebugTextToVSOutput true

#else

//DO NOT TOUCH THESE
#define EnableMultiThreading true //Force draw to be on a second thread
#define EnableEngineThreadSpeedTracking false //Force profiling to be turned off
#define IgnoreTrivialSpeedTrackingResults false
#define EnableEngineThreadDebugLog false
#define EnableWarningLog false
#define PrintDebugTextToVSOutput false

#endif _DEBUG





//Use this file to save all of the static values for the arrays of engine resources that you'd like to be available to the user.
//This will include all of the header objects that we need for all of our gameobject components.

static const unsigned int MaxNumberOfLiveUpdateComponents = 15u;
static const unsigned int MaxNumberOfLiveAlarms = 10u;
static const unsigned int InitialWindowHeight = 720;
static const unsigned int InitialWindowWidth = 1280;
static const bool EnableVSync = false;

static const int MaxGraphicsObjectInstances = 10000;

static const int targetFPS = 100;

#endif // !ENGINESETTINGS_H
