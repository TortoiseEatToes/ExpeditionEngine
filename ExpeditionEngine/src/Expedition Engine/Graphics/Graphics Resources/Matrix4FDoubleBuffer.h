#pragma once

#include "../../Containers/List.h"
#include "../../Math/Base/Align16.h"

#include "Matrix4FDoubleBufferSynchClean.h"
#include "Matrix4FDoubleBufferSynchDirty.h"

#include "../../Math/Matrix/Matrix4F.h"

class Matrix4FDoubleBuffer : public Align16
{
public:
	Matrix4FDoubleBuffer() = default;
	Matrix4FDoubleBuffer(const Matrix4F& startingValue);
	Matrix4FDoubleBuffer(const Matrix4FDoubleBuffer& other) = delete;
	Matrix4FDoubleBuffer& operator= (const Matrix4FDoubleBuffer& other) = delete;
	~Matrix4FDoubleBuffer() = default;


	//Draw functions
	void SetDraw(const Matrix4F& newValue) { drawBuffer = newValue; }
	Matrix4F& GetDraw() { return drawBuffer; }
	

	//Update functions
	void SetUpdate(const Matrix4F& newValue) { updateBuffer = newValue; pCurrentStrategy = &dirtyStrategy;}
	Matrix4F& GetUpdate() { return updateBuffer;}

	/// <summary>Initialize this double buffer after acquiring it. INITIALIZE MUST BE CALLED EVERY TIME YOU ACQUIRE A DOUBLE BUFFER.</summary>
	/// <param name="startingValue">const reference to a matrix that the update and draw buffer should be set as equal to</param>
	void Initialize(const Matrix4F& startingValue);

private:
	friend class Matrix4FDoubleBufferAttorney;

	void Synchronize();

	Matrix4F updateBuffer;
	Matrix4F drawBuffer;
	static Matrix4FDoubleBufferSynchClean cleanStrategy;
	static Matrix4FDoubleBufferSynchDirty dirtyStrategy;
	Matrix4FDoubleBufferSynchStrategy* pCurrentStrategy = &cleanStrategy;
};