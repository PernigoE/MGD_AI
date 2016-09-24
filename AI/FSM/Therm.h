#pragma once

#include "FSM.h"
#include "ThermIdle.h"
#include <iostream>

class Therm
{
private:
	FSM<Therm>* m_oFSM;
	float m_fTemp;
	float m_fTempLimit;

public:
	Therm()
	{
		m_oFSM = new FSM<Therm>(ThermIdle::Instance());
	}

	float GetTemp() const
	{
		return m_fTemp;
	}

	float GetTempLimit() const
	{
		return m_fTempLimit;
	}

	FSM<Therm>* GetFSM()
	{
		return m_oFSM;
	}

	void Update()
	{
		m_oFSM->Update();
	}
};