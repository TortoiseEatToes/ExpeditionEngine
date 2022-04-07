#pragma once

class Component
{
public:

	/// <summary>Override what this object should do when the owning manager gets Process called on it.</summary>
	virtual void Process() = 0;

	/// <summary>Don't forget to override the assignment operator.</summary>
};