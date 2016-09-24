#pragma once

#include "BaseState.h"
#include "Therm.h"
#include "ThermHeat.h"

class ThermIdle : public BaseState<Therm>
{
private:
	ThermIdle();

public:
	static ThermIdle* Instance()
	{
		static ThermIdle s;
		return &s;
	}

	void OnEnter(Therm* a)
	{
		
	}

	void OnUpdate(Therm* a)
	{
		if (a->GetTemp() < a->GetTempLimit())
		{
			a->GetFSM()->DoTransition(ThermHeat::Instance());
			std::cout << "Therm On\n";
		}
	}

	void OnExit(Therm* a)
	{

	}

};