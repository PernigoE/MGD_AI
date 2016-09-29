#include "Therm.h"
#include "ThermIdle.h"

Therm::Therm()
{
	m_oFSM = new FSM<Therm>(ThermIdle::Instance());
}
