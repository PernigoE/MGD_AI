#include "MinerSleep.h"
#include "MinerIdle.h"

void MinerSleep::OnEnter(Miner * m)
{
	m->currState = Miner::State::SLEEP;
	m_fTimeIn = std::chrono::high_resolution_clock::now();
	m_fTime = 8000;
}

void MinerSleep::OnUpdate(Miner * m)
{
	float m_fDeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_fTimeIn).count();
	m_fTime -= m_fDeltaTime;
	m_fTimeIn = std::chrono::high_resolution_clock::now();
	
	m->DecreaseTiredness(m_fDeltaTime);

	if (m_fTime < 0)
	{
		m->GetFSM()->DoTransition(m, MinerIdle::Instance());
	}
}

void MinerSleep::OnExit(Miner * m)
{
}
