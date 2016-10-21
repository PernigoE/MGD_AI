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
		//qui li metto a zero perchè creo un nuovo nodo e uso solo quello di partenza come base.
		m_iH = 0;
		m_iG = 0;
		m_iF = 0;

		for (int i = 0; i < 16; ++i)
		{
			State[i] = other.State[i];
		}
		
		m_pParent = &other; //si, perchè voglio il nodo di partenza come parent per creare le mosse
	}

	Node15& operator=(Node15& other)
	{
		m_iH = other.m_iH; //l'euristica rimane uguale
		//questi due preferisco copiarmeli nel caso volessi fare un controllo
		m_iG = other.m_iG;
		m_iF = other.m_iF;

		for (int i = 0; i < 16; ++i)
		{
			State[i] = other.State[i];
		}

		m_pParent = other.m_pParent; // devo copiare anche il parent

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