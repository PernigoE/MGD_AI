#pragma once
#include <chrono>
#include "../FSM/BaseState.h"
#include "Miner.h"

class MinerIdle : public BaseState<Miner>
{
private:
	MinerIdle() = default;
	std::chrono::high_resolution_clock::time_point m_fTime;

public:
	static MinerIdle* Instance()
	{
		static MinerIdle s;
		return &s;
	}

	void OnEnter(Miner* m);
	void OnUpdate(Miner* m);
	void OnExit(Miner* m);
};