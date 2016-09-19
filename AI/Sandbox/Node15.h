#pragma once

#include <list>
#include <iostream>

struct Node15
{
	int State[16];
	std::list<Node15*> m_aAdj;

	int m_iH;
	int m_iG;
	int m_iF;

	Node15* m_pParent;

	Node15()
	{
		m_iH = 0;
		m_iG = 0;
		m_iF = 0;

		m_pParent = nullptr;
	}

	Node15(Node15& other)
	{
		m_iH = 0;
		m_iG = 0;
		m_iF = 0;

		for (int i = 0; i < 16; ++i)
		{
			State[i] = other.State[i];
		}
		m_pParent = &other;
	}

	Node15& operator=(Node15& other)
	{
		m_iH = 0;
		m_iG = 0;
		m_iF = 0;

		for (int i = 0; i < 16; ++i)
		{
			State[i] = other.State[i];
		}

		m_pParent = &other;

		return *this;
	}


	bool operator==(Node15& other)
	{
		for (int i = 0; i < 16; ++i)
		{
			if (State[i] != other.State[i])
				return false;
		}
		return true;
	}

	bool operator!=(Node15& other)
	{
		return !(*this == other);
	}
};