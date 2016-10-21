#pragma once

#include "FSM.h"
//#include "ThermIdle.h"
#include <iostream>

class Therm
{
private:
	FSM<Therm>* m_oFSM;
	float m_fTemp = 12;
	float m_fTempLimit = 15;

public:
	Therm();

	void SetTemp(float temp)
	{
		m_fTemp = temp;
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
		m_oFSM->Update(this);
	}
};