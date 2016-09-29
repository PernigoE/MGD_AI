#pragma once
#include <list>

#include "BaseState.h"

template<typename Agent>
class FSM
{
private:
	BaseState<Agent> *m_pCurrentState;

public:
	FSM() = delete;
	FSM(BaseState<Agent>* state)
	{
		m_pCurrentState = state;
	}

	void Start(Agent* agent)
	{
		m_pCurrentState->OnEnter(agent);
	}

	void DoTransition(Agent* agent, BaseState<Agent>* next)
	{
		m_pCurrentState->OnExit(agent);
		m_pCurrentState = next;
		m_pCurrentState->OnEnter(agent);
	}

	void Update(Agent* agent)
	{
		m_pCurrentState->OnUpdate(agent);
	}

	void Exit(Agent* agent)
	{
		m_pCurrentState->OnExit(agent);
	}
};