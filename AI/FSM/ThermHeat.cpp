#include "ThermHeat.h"
#include "ThermIdle.h"

void ThermHeat::OnUpdate(Therm * a)
{
	if (a->GetTemp() > a->GetTempLimit())
	{
		a->GetFSM()->DoTransition(a, ThermIdle::Instance());
		std::cout << "Therm Off\n";
	}
}
