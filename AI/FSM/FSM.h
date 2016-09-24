#pragma once
#include <list>

#include "BaseState.h"

template<typename Agent>
class FSM
{
private:
	BaseState *m_pCurrentState;

public:
	FSM() = delete;
	FSM(BaseState* state)
	{
		m_pCurrentState = state;
	}

	void Start()
	{
		m_pCurrentState->OnEnter();
	}

	void DoTransition(BaseState* next)
	{
		m_pCurrentState->OnExit();
		m_pCurrentState = next;
		m_pCurrentState->OnEnter();
	}

	void Update()
	{
		m_pCurrentState->OnUpdate();
	}

	void Exit()
	{
		m_pCurrentState->OnExit();
	}
};