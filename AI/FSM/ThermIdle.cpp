#include "ThermIdle.h"
#include "ThermHeat.h"
void ThermIdle::OnUpdate(Therm * a)
{
	if (a->GetTemp() < a->GetTempLimit())
	{
		a->GetFSM()->DoTransition(a , ThermHeat::Instance());
		std::cout << "Therm On\n";
	}
}
