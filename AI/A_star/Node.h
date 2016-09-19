#pragma once

#include <list>
#include <map>

enum NodeState
{
	NOT_VISITED,
	IN_OPEN,
	IN_CLOSED
};

struct Node
{
	std::map<Node*,int> m_aAdj;

	int m_iRow;
	int m_iCol;

	int m_iH;
	int m_iG;
	int m_iF;

	Node* m_pParent;

	NodeState m_eState;

	Node() {
		m_iH = 0;
		m_iG = 0;
		m_iF = 0;

		m_eState = NOT_VISITED;

		m_pParent = nullptr;
	}
};