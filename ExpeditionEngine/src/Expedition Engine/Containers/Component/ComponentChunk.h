#pragma once

#include ""

template <typename Component>
class ComponentChunk
{
public:
	ComponentChunk() = delete;
	ComponentChunk(const int& size);
	ComponentChunk(const ComponentChunk&) = delete;
	ComponentChunk& operator= (const ComponentChunk&) = delete;
	~ComponentChunk();

private:
	Component* pComponentArray = nullptr;
	int size = -1;
	int unusedIndex = -1;
};