#pragma once

#include <chrono>
#include "../FSM/BaseState.h"
#include "Miner.h"

class MinerTravel : public BaseState<Miner>
{
private:
	MinerTravel() = default;
	std::chrono::high_resolution_clock::time_point m_fTimeIn;
	float m_fTime;

public:
	static MinerTravel* Instance()
	{
		static MinerTravel s;
		return &s;
	}

	void OnEnter(Miner* m);
	void OnUpdate(Miner* m);
	void OnExit(Miner* m);
};