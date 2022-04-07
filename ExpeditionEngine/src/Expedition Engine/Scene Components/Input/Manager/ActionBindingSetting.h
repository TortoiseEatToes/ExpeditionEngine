#pragma once



struct ActionBindingSetting
{
	enum Type
	{
		Keyboard,
		Mouse,
		Unbound
	};

	Type actionBindingType = Type::Unbound;
	int index = -1;
};