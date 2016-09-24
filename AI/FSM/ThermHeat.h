#pragma once

#include "ThermIdle.h"
#include "BaseState.h"
#include "Therm.h"

class ThermHeat : public BaseState<Therm>
{
private:
	ThermHeat();

public:
	static ThermHeat* Instance()
	{
		static ThermHeat s;
		return &s;
	}

	void OnEnter(Therm* a)
	{

	}

	void OnUpdate(Therm* a)
	{
		if (a->GetTemp() > a->GetTempLimit())
		{
			a->GetFSM()->DoTransition(ThermIdle::Instance());
			std::cout << "Therm Off\n";
		}
	}

	void OnExit(Therm* a)
	{

	}
};