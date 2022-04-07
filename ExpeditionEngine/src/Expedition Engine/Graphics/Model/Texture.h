// Texture
// Andre Berthiaume, July, 2016

#ifndef _Texture
#define _Texture

#include <Windows.h>
#include <string>
#include <d3d12.h>
#include "../../../Expedition Resources/TextureSettings.h"

class Texture
{
public:
	Texture(const Texture&) = delete;				 // Copy constructor
	Texture(Texture&&) = delete;                    // Move constructor
	Texture& operator=(const Texture&) & = delete;  // Copy assignment operator
	Texture& operator=(Texture&&) & = delete;       // Move assignment operator
	~Texture();									     // Destructor
	Texture() = delete;

	Texture(LPCWSTR filepath, ID3D12GraphicsCommandList4* cmdlist, TextureName initName, UINT isotropic_level = 4, bool ComputeMip = false, size_t miplevel = 0);

	ID3D12Resource* GetResource()
	{
		return g_Resource;
	}

private:
	ID3D12Resource* g_Resource;
	ID3D12Resource* g_UploadHeap;

	int textureWidth;
	int textureHeight;

	TextureName name;

public:
	int getWidth()
	{
		return this->textureWidth;
	};
	int getHeight()
	{
		return this->textureHeight;
	};

	TextureName& getName()
	{
		return name;
	}

};

#endif _Texture