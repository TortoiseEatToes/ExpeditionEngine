#pragma once
#include "../../Containers/List.h"
#include "Vector4FDoubleBufferSynchClean.h"
#include "Vector4FDoubleBufferSynchDirty.h"


#include "../../Math/Base/Align16.h"

class Vector4FDoubleBuffer : public Align16
{
public:
	Vector4FDoubleBuffer() = default;
	Vector4FDoubleBuffer(const Vector4F& startingValue);
	Vector4FDoubleBuffer(const Vector4FDoubleBuffer& other) = delete;
	Vector4FDoubleBuffer& operator= (const Vector4FDoubleBuffer& other) = delete;
	~Vector4FDoubleBuffer() = default;


	//Set Draw functions
	void SetDraw(const Vector4F& newValue) { drawBuffer = newValue; }
	void SetDrawAttribute0(Texture& newValue) { drawBuffer.attribute0.pTexture = &newValue; }
	void SetDrawAttribute1(Texture& newValue) { drawBuffer.attribute1.pTexture = &newValue; }
	void SetDrawAttribute2(Texture& newValue) { drawBuffer.attribute2.pTexture = &newValue; }
	void SetDrawAttribute3(Texture& newValue) { drawBuffer.attribute3.pTexture = &newValue; }

	//Get Draw functions
	Vector4F& GetDraw() { return drawBuffer; }
	Vector4F::Attribute& GetDrawAttribute0() { return drawBuffer.attribute0; }
	Vector4F::Attribute& GetDrawAttribute1() { return drawBuffer.attribute1; }
	Vector4F::Attribute& GetDrawAttribute2() { return drawBuffer.attribute2; }
	Vector4F::Attribute& GetDrawAttribute3() { return drawBuffer.attribute3; }

	//Update functions
	void SetUpdate(const Vector4F& newValue) { updateBuffer = newValue; pCurrentStrategy = &dirtyStrategy; }
	void SetUpdateAttribute0(Texture& newValue) { updateBuffer.attribute0.pTexture = &newValue; pCurrentStrategy = &dirtyStrategy; }
	void SetUpdateAttribute1(Texture& newValue) { updateBuffer.attribute1.pTexture = &newValue; pCurrentStrategy = &dirtyStrategy; }
	void SetUpdateAttribute2(Texture& newValue) { updateBuffer.attribute2.pTexture = &newValue; pCurrentStrategy = &dirtyStrategy; }
	void SetUpdateAttribute3(Texture& newValue) { updateBuffer.attribute3.pTexture = &newValue; pCurrentStrategy = &dirtyStrategy; }
	
	Vector4F& GetUpdate() { return updateBuffer; }
	Vector4F::Attribute& GetUpdateAttribute0() { return updateBuffer.attribute0; }
	Vector4F::Attribute& GetUpdateAttribute1() { return updateBuffer.attribute1; }
	Vector4F::Attribute& GetUpdateAttribute2() { return updateBuffer.attribute2; }
	Vector4F::Attribute& GetUpdateAttribute3() { return updateBuffer.attribute3; }

	/// <summary>Initialize this double buffer after acquiring it. INITIALIZE MUST BE CALLED EVERY TIME YOU ACQUIRE A DOUBLE BUFFER.</summary>
	/// <param name="startingValue">const reference to a vector that the update and draw buffer should be set as equal to</param>
	void Initialize(const Vector4F& startingValue);

private:
	friend class Vector4FDoubleBufferAttorney;

	void Synchronize();

	Vector4F updateBuffer;
	Vector4F drawBuffer;
	static Vector4FDoubleBufferSynchClean cleanStrategy;
	static Vector4FDoubleBufferSynchDirty dirtyStrategy;
	Vector4FDoubleBufferSynchStrategy* pCurrentStrategy = &cleanStrategy;
};