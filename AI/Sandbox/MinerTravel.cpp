#include "MinerTravel.h"
#include "MinerIdle.h"
#include "MinerWork.h"

void MinerTravel::OnEnter(Miner * m)
{
	m->currState = Miner::State::TRAVEL;
	m_fTimeIn = std::chrono::high_resolution_clock::now();
	m_fTime = 3000;
}

void MinerTravel::OnUpdate(Miner * m)
{
	int m_fDeltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_fTimeIn).count();
	m_fTime -= m_fDeltaTime;
	m_fTimeIn = std::chrono::high_resolution_clock::now();

	if (m_fTime < 0)
	{
		if (m->nextState == Miner::State::MINE)
		{
			m->GetFSM()->DoTransition(m, MinerWork::Instance());
		}
		else
		{
			m->GetFSM()->DoTransition(m, MinerIdle::Instance());
		}
	}
}

void MinerTravel::OnExit(Miner * m)
{
}
