#include "ThermHeat.h"
#include "ThermIdle.h"

void ThermHeat::OnEnter(Therm * a)
{
}

void ThermHeat::OnUpdate(Therm * a)
{
	if (a->GetTemp() > a->GetTempLimit())
	{
		a->GetFSM()->DoTransition(a, ThermIdle::Instance());
		std::cout << "Therm Off\n";
	}
}

void ThermHeat::OnExit(Therm * a)
{
}
