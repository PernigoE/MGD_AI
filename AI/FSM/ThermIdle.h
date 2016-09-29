#pragma once

#include "BaseState.h"
#include "Therm.h"

class ThermIdle : public BaseState<Therm>
{
private:
	ThermIdle() = default;

public:
	static ThermIdle* Instance()
	{
		static ThermIdle s;
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