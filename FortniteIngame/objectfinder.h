#pragma once

#include <string>

#include "uestruct.h"

template <typename T = UObject*>
T FindObject(std::string obj)
{
	// Loop through each Object
	for (uint32_t i = 0u; i < ObjObjects->NumElements; i++)
	{
		auto object = GetObjectById(i);
		if (object && object->GetFullName() == name) { return (T)object; } // Checks if the current iteration is what we are looking for, if it is then it casts the Object to the return template type and returns.
	}
	return nullptr;
}