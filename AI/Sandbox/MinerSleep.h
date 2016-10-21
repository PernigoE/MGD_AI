#pragma once
#include <chrono>
#include "../FSM/BaseState.h"
#include "Miner.h"

class MinerSleep : public BaseState<Miner>
{
private:
	MinerSleep() = default;
	std::chrono::high_resolution_clock::time_point m_fTimeIn;
	float m_fTime;

public:
	static MinerSleep* Instance()
	{
		static MinerSleep s;
		return &s;
	}

	void OnEnter(Miner* m);
	void OnUpdate(Miner* m);
	void OnExit(Miner* m);
};