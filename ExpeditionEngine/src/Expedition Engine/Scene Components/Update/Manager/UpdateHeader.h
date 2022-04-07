#pragma once

class UpdateComponent;

class UpdateHeader
{
public:
	UpdateHeader() = default;
	UpdateHeader(const UpdateHeader& other) = delete;
	UpdateHeader& operator= (const UpdateHeader& other) = delete;
	~UpdateHeader() = default;

	UpdateHeader* pNext;
	UpdateHeader* pPrevious;
	UpdateComponent* pComponent;
};