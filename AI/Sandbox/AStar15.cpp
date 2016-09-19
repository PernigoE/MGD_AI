#include <algorithm>
#include <Windows.h>

#include "AStar15.h"

void AStar15::CreateGraph()
{
	pStartNode = new Node15();
	pEndNode = new Node15();

	pCurrNode = pStartNode;
	pCurrNode->m_pParent = pCurrNode;

	for (int i = 0; i < 16; ++i)
	{
		pStartNode->State[i] = i;
		pEndNode->State[i] = i;
	}

	std::swap(pStartNode->State[0], pStartNode->State[4]);
	std::swap(pStartNode->State[0], pStartNode->State[1]);

}

AStar15::~AStar15()
{

	//while (!qOpenList.empty())
	//{
	//	delete qOpenList.front();
	//	qOpenList.pop_front();
	//}

	//while (!qClosedList.empty())
	//{
	//	delete qClosedList.front();
	//	qClosedList.pop_front();
	//}

	//delete pStartNode;
	//delete pEndNode;
}


void AStar15::CreateGraphAdjs()
{
}

int AStar15::GetZeroPos(Node15* node)
{
	for (int i = 0; i < 16; ++i)
	{
		if (node->State[i] == 0)
			return i;
	}
}

void AStar15::AdjZeroUp(Node15* node)
{
	int zeroPos = GetZeroPos(node);

	Node15* n = new Node15{ *node };
	if (zeroPos > 3)
	{
		//swap if is out of bound
		std::swap(n->State[zeroPos], n->State[zeroPos - 4]);
	}
	else
	{
		//else shift down 
		n->State[zeroPos] = n->State[zeroPos + 4];
		n->State[zeroPos + 4] = n->State[zeroPos + 8];
		n->State[zeroPos + 8] = n->State[zeroPos + 12];
		n->State[zeroPos + 12] = 0;
	}

	if (*n == *node->m_pParent)
	{
		delete n;
	}
	else
	{
		node->m_aAdj.push_back(n);
	}
	
}

void AStar15::AdjZeroDown(Node15* node)
{
	int zeroPos = GetZeroPos(node);

	Node15* n = new Node15{ *node };
	if (zeroPos < 12)
	{
		std::swap(n->State[zeroPos], n->State[zeroPos + 4]);
	}
	else
	{
		n->State[zeroPos] = n->State[zeroPos - 4];
		n->State[zeroPos - 4] = n->State[zeroPos - 8];
		n->State[zeroPos - 8] = n->State[zeroPos - 12];
		n->State[zeroPos - 12] = 0;
	}

	if (*n == *node->m_pParent)
	{
		delete n;
	}
	else
	{
		node->m_aAdj.push_back(n);
	}
}

void AStar15::AdjZeroLeft(Node15* node)
{
	int zeroPos = GetZeroPos(node);

	Node15* n = new Node15{ *node };
	if (zeroPos % 4 > 0)
	{
		std::swap(n->State[zeroPos], n->State[zeroPos - 1]);
	}
	else
	{
		n->State[zeroPos] = n->State[zeroPos + 1];
		n->State[zeroPos + 1] = n->State[zeroPos + 2];
		n->State[zeroPos + 2] = n->State[zeroPos + 3];
		n->State[zeroPos + 3] = 0;
	}

	if (*n == *node->m_pParent)
	{
		delete n;
	}
	else
	{
		node->m_aAdj.push_back(n);
	}
}

void AStar15::AdjZeroRight(Node15* node)
{
	int zeroPos = GetZeroPos(node);

	Node15* n = new Node15{ *node };
	if (zeroPos % 4 < 3)
	{
		std::swap(n->State[zeroPos], n->State[zeroPos + 1]);
	}
	else
	{
		n->State[zeroPos] = n->State[zeroPos - 1];
		n->State[zeroPos - 1] = n->State[zeroPos - 2];
		n->State[zeroPos - 2] = n->State[zeroPos - 3];
		n->State[zeroPos - 3] = 0;
	}

	if (*n == *node->m_pParent)
	{
		delete n;
	}
	else
	{
		node->m_aAdj.push_back(n);
	}
}


void AStar15::CreateNodeAdj(Node15* node)
{
	AdjZeroUp(node);

	AdjZeroDown(node);

	AdjZeroLeft(node);

	AdjZeroRight(node);
}

void AStar15::ComputeGraphHeuristics()
{

}

//sum of all distance beetween numbers and its target pos
void AStar15::ComputeNodeHeuristic(Node15* pNode)
{
	int result = 0;
	for (int i = 0; i < 16; ++i)
	{
		if (pNode->State[i] != 0)
		{
			int iRow = i / 4;
			int iCol = i % 4;

			int iTargetRow = pNode->State[i] / 4;
			int iTargetCol = pNode->State[i] % 4;

			result += abs(iRow - iTargetRow) + abs(iCol - iTargetCol);
		}
	}
	pNode->m_iH = result;
}

void AStar15::Clean()
{
	qOpenList.clear();
	qClosedList.clear();
}

void AStar15::Search()
{
	qOpenList.push_back(pStartNode);

	while (!qOpenList.empty())
	{
		pCurrNode = VisitNode();
		//clear the openlist??
		qOpenList.clear();
		if (*pCurrNode != *pEndNode) 
		{
			//add the almost 4 neighboar
			CreateNodeAdj(pCurrNode);

			//add neighboar to open list
			std::list<Node15*>::const_iterator it = pCurrNode->m_aAdj.begin();
			for (; it != pCurrNode->m_aAdj.end(); ++it)
			{
				AddNodeToOpenList(pCurrNode, *it);
			}
		}
		else
		{
			std::cout << "\nSolution Find\n";
			return;
		}

		Sleep(200);
	}

}

//take the F lower Node
Node15* AStar15::VisitNode()
{
	Node15* minGNode = qOpenList.front();

	std::list<Node15*>::iterator index = qOpenList.begin();
	for (std::list<Node15*>::iterator it = ++qOpenList.begin(); it != qOpenList.end(); ++it)
	{
		if ((*it)->m_iF < minGNode->m_iF)
		{
			minGNode = (*it);
			index = it;
		}
	}
	qClosedList.push_back(minGNode);
	qOpenList.erase(index);
	return minGNode;
}

void AStar15::AddNodeToOpenList(Node15* pParent, Node15* pNode)
{
	//search the node in closed list, if there is exit function
	std::list<Node15*>::iterator it = qClosedList.begin();
	for (; it != qClosedList.end(); ++it)
	{
		if (*(*it) == *pNode)
		{
			return;
		}
	}

	//serach node in open list, if there is update node ??
	it = qOpenList.begin();
	for (; it != qOpenList.end(); ++it)
	{
		if (*(*it) == *pNode)
		{
			if (pNode->m_iG > pParent->m_iG + 1)
			{
				pNode->m_pParent = pParent;
				pNode->m_iG = pParent->m_iG + 1;
				pNode->m_iF = pNode->m_iG + pNode->m_iH;
				return;
			}
		}
	}

	//valorize the node value for the first time
	ComputeNodeHeuristic(pNode);

	pNode->m_pParent = pParent;
	//weight is always 1
	pNode->m_iG = pParent->m_iG + 1;
	pNode->m_iF = pNode->m_iG + pNode->m_iH;

	qOpenList.push_back(pNode);
}

AStar15::AStar15()
{
	CreateGraph();
}

void AStar15::Run() {

	Search();
}

Node15* AStar15::GetCurrNode()
{
	return pCurrNode;
}
