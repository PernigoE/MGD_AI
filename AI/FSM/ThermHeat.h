#pragma once


#include "BaseState.h"
#include "Therm.h"

class ThermHeat : public BaseState<Therm>
{
private:
	ThermHeat() = default;

public:
	static ThermHeat* Instance()
	{
		static ThermHeat s;
		return &s;
	}

	void OnEnter(Therm* a)
	{

	}

	void OnUpdate(Therm* a);
	void OnExit(Therm* a)
	{

	}
};