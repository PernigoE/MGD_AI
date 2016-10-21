#pragma once
#include "../FSM/FSM.h"

class Miner
{
public:
	enum State
	{
		HOME,
		TRAVEL,
		MINE,
		SLEEP
	};

private:
	FSM<Miner>* m_pFSM;
	float m_iTiredness;
	int m_iGold;

	const float mk_fLoadPerSec;
	const int mk_iGoldLimit;
	const int mk_iTiredLimit;

public:
	State currState;
	State nextState;

	Miner(float _loadPerSec, int goldLimit, int tiredLimit);

	FSM<Miner>* GetFSM();
	void Update();

	void IncreaseTiredness(float);
	void DecreaseTiredness(float);
	int GetTired() const;
	bool EnoughTired() const;

	void IncreaseGold(int);
	void DecreaseGold(int);
	int GetGold() const;
	bool EnoughGold() const;

};