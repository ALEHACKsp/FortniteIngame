#pragma once

#include "uestruct.h"
#include "objectfinder.h"

FChunkFixedUObjectArray* ObjObjects = nullptr;
void (*FNameToString)(FName* In, FString& Out); // https://github.com/EpicGames/UnrealEngine/blob/99b6e203a15d04fc7bbbf554c421a985c1ccb8f1/Engine/Source/Runtime/Core/Private/UObject/UnrealNames.cpp#L2213
void* (*ProcessEvent)(void* Object, void* Function, void* Params); // https://github.com/EpicGames/UnrealEngine/blob/99b6e203a15d04fc7bbbf554c421a985c1ccb8f1/Engine/Source/Runtime/CoreUObject/Private/UObject/ScriptCore.cpp#L1848

template <typename T>
void EProcessEvent(const wchar_t* function, T params, UObject* Outer = nullptr)
{

	if (!Outer)
	{
		if (wcsstr(function, XOR(L".FortPlayerController"))) Outer = GetPlayerController();
		else if (wcsstr(function, XOR(L".FortPlayerPawn")) || wcsstr(function, XOR(L".FortPawn"))) Outer = GetPlayerPawn();
		else if (wcsstr(function, XOR(L".FortKismetLibrary."))) Outer = UE4::FindObject<UObject*>(XOR(L"FortKismetLibrary /Script/FortniteGame.Default__FortKismetLibrary"));
	}
	if (!Outer) return;
	void* PEF = UE4::FindObject(function);
	if (wcsstr(function, L"Function ")) PEF = FindObject<UFunction*>(function);
	else if (wcsstr(function, L"Class ")) PEF = FindObject<UClass*>(function);
	ProcessEvent(Outer, PEF, &params);
}