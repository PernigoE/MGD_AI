#include "MinerWork.h"
#include "MinerTravel.h"

void MinerWork::OnEnter(Miner * m)
{
	m->currState = Miner::State::MINE;
	m_fTimeIn = std::chrono::high_resolution_clock::now();
}

void MinerWork::OnUpdate(Miner * m)
{
	float m_fDeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_fTimeIn).count();
	m_fTimeIn = std::chrono::high_resolution_clock::now();

	m->IncreaseGold(1);
	m->IncreaseTiredness(m_fDeltaTime);
	if (m->EnoughGold() || m->EnoughTired())
	{
		m->nextState = Miner::State::HOME;
		m->GetFSM()->DoTransition(m, MinerTravel::Instance());
	}

}

void MinerWork::OnExit(Miner * m)
{
}
