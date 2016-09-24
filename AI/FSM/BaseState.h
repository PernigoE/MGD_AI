#pragma once

#include "BaseState.h"
#include "Therm.h"

template<class T>
class BaseState
{
public:
	virtual ~BaseState() {};

	virtual void OnEnter(T*) = 0;
	virtual void OnUpdate(T*) = 0;
	virtual void OnExit(T*) = 0;
};