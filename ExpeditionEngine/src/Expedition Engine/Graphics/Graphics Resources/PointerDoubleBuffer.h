#pragma once
#include "../../Containers/List.h"

#include "../../Math/Base/Align16.h"
#include "../../../Expedition Resources/TextureSettings.h"

class Texture;

class PointerDoubleBuffer
{
public:
	PointerDoubleBuffer() = default;
	PointerDoubleBuffer(const PointerDoubleBuffer& other) = delete;
	PointerDoubleBuffer& operator= (const PointerDoubleBuffer& other) = delete;
	~PointerDoubleBuffer() = default;


	union PointerType
	{
		Texture* texture;
		TextureName textureName;
	};

	//Draw functions
	void SetDraw(Texture*& newValue) { drawBuffer.texture = newValue; }
	Texture*& GetDrawTexture() { return drawBuffer.texture; }

	void SetDraw(const TextureName& newValue) { drawBuffer.textureName = newValue; }
	const TextureName& GetDrawTextureName() { return drawBuffer.textureName; }

	//Update functions
	void SetUpdate(Texture*& newValue) { updateBuffer.texture = newValue; }
	Texture*& GetUpdateTexture() { return updateBuffer.texture; }

	void SetUpdate(const TextureName& newValue) { updateBuffer.textureName = newValue; }
	const TextureName& GetUpdateTextureName() { return updateBuffer.textureName; }
	/// <summary>Initialize this double buffer after acquiring it. INITIALIZE MUST BE CALLED EVERY TIME YOU ACQUIRE A DOUBLE BUFFER.</summary>
	/// <param name="startingValue">const reference to a texture pointer that the update and draw buffer should be set as equal to</param>
	void Initialize(Texture*& startingValue);


private:
	friend class PointerDoubleBufferAttorney;

	void Synchronize();

	PointerType updateBuffer;
	PointerType drawBuffer;
};