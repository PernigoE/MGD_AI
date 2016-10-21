#include "Miner.h"
#include "MinerIdle.h"

Miner::Miner(float _loadPerSec, int goldLimit, int tiredLimit) : mk_fLoadPerSec(_loadPerSec), mk_iGoldLimit(goldLimit), mk_iTiredLimit(tiredLimit)
{
	currState = State::HOME;
	nextState = State::HOME;
	m_iGold = 10;
	m_iTiredness = 0;
	m_pFSM = new FSM<Miner>(MinerIdle::Instance());
};

void Miner::IncreaseTiredness(float value)
{
	m_iTiredness += value / 1000;
}

void Miner::IncreaseGold(int value)
{
	m_iGold += value;
}


void Miner::DecreaseTiredness(float value)
{
	m_iTiredness -= value * mk_fLoadPerSec / 1000;
}

void Miner::DecreaseGold(int value)
{
	m_iGold -= value;
}

int Miner::GetTired() const
{
	return (int)m_iTiredness;
}

bool Miner::EnoughTired() const
{
	return m_iTiredness >= mk_iTiredLimit;
}

bool Miner::EnoughGold() const
{
	return m_iGold > mk_iGoldLimit;
}

FSM<Miner>* Miner::GetFSM()
{
	return m_pFSM;
}

void Miner::Update()
{
	m_pFSM->Update(this);
}

int Miner::GetGold() const
{
	return m_iGold;
}
