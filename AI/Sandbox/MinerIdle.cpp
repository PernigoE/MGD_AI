#include "MinerIdle.h"
#include "MinerTravel.h"
#include "MinerSleep.h"

void MinerIdle::OnEnter(Miner * m)
{
	m->currState = Miner::State::HOME;
}

void MinerIdle::OnUpdate(Miner * m)
{
	if (m->EnoughTired())
	{
		m->GetFSM()->DoTransition(m, MinerSleep::Instance());
	}

	m->DecreaseGold(1);
	if (m->GetGold() <= 0)
	{
		m->nextState = Miner::State::MINE;
		m->GetFSM()->DoTransition(m, MinerTravel::Instance());
	}
}

void MinerIdle::OnExit(Miner * m)
{
}
