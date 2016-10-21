#pragma once

#include <chrono>
#include "../FSM/BaseState.h"
#include "Miner.h"

class MinerWork : public BaseState<Miner>
{
private:
	MinerWork() = default;
	std::chrono::high_resolution_clock::time_point m_fTimeIn;
	float m_fTime;

public:
	static MinerWork* Instance()
	{
		static MinerWork s;
		return &s;
	}

	void OnEnter(Miner* m);
	void OnUpdate(Miner* m);
	void OnExit(Miner* m);
};