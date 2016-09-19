#pragma once

#include <list>
#include <map>

enum NodeState
{
	NOT_VISITED,
	IN_OPEN,
	IN_CLOSED,
	IN_PATH,
	SELECTED
};

struct Node
{
	//std::map<Node*,int> m_aAdj;
	std::map<Node*, float> m_aAdj;

	int m_iRow;
	int m_iCol;

	float m_iH;
	float m_iG;
	float m_iF;

	Node* m_pParent;

	NodeState m_eState;

	Node() {
		m_iH = 0.0f;
		m_iG = 0.0f;
		m_iF = 0.0f;

		m_eState = NOT_VISITED;

		m_pParent = nullptr;
	}
};