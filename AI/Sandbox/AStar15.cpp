#include <algorithm>
#include <Windows.h>

#include "AStar15.h"

void AStar15::CreateGraph()
{
	pStartNode = new Node15();
	pEndNode = new Node15();

	/*Assolutamente no, pCurrent tanto lo modifichi appena fai il search e vuoi
	il nodo di partenza con parent null per controllo fine ricerca all'indietro.
	Bisogna prima far girare AStar e poi stampare i nodi.*/
	//pCurrNode->m_pParent = pCurrNode;

	//combinazioni conosiute per test
	//{ 4, 1, 2, 3, 8, 5, 10, 6, 12, 9, 15, 0, 13, 14, 11, 7 }
	int start[16] = { 4, 1, 2, 3, 8, 5, 10, 6, 12, 9, 15, 0, 13, 14, 11, 7 };
	for (int i = 0; i < 16; ++i)
	{
		pStartNode->State[i] = start[i];
		pEndNode->State[i] = i;
	}
	pCurrNode = pStartNode; //per semplicità di stampa

	/*
	//std::swap(pStartNode->State[0], pStartNode->State[4]);
	//std::swap(pStartNode->State[0], pStartNode->State[1]);

	for (int i = 0; i < 50; ++i)
	{
		Node15* n = NeighbourByMove(pCurrNode, Moves[rand() % 4]);
		if (n != nullptr)
		{
			pCurrNode = n;
		}
	}
	pStartNode = pCurrNode;*/

	
	
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
	//si potrebbe migliorare salvandosi dove si trova lo zero
	//ma lasciamo così che tanto è uguale
	for (int i = 0; i < 16; ++i)
	{
		if (node->State[i] == 0)
			return i;
	}
}

Node15 * AStar15::NeighbourByMove(Node15 *node, MOVES move)
{
	int zeroPos = GetZeroPos(node);
	int newZeroPos = (int)move + zeroPos;
	int rowDiff = (int)move % 4;
	if (newZeroPos < 0 || newZeroPos > 15 || (newZeroPos % 4) - (zeroPos % 4) != rowDiff)
	{
		return nullptr;
	}
	else
	{
		Node15* n = new Node15{ *node };
		std::swap(n->State[zeroPos], n->State[newZeroPos]);
		return n;
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
	/*
	AdjZeroUp(node);

	AdjZeroDown(node);

	AdjZeroLeft(node);

	AdjZeroRight(node);
	*/
	//provo con la nuova funzione
	for (const auto move : Moves)
	{
		Node15* neighbor = NeighbourByMove(node, move);
		if (neighbor != nullptr)
		{
			node->m_aAdj.push_back(neighbor);
		}
	}
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
		if (pNode->State[i] != 0) //perchè escludere lo zero?
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
	Sleep(400);
	qOpenList.push_back(pStartNode);

	while (!qOpenList.empty())
	{
		pCurrNode = VisitNode();
		//clear the openlist??
		//Non puoi fare la clear della open list altrimenti non prenderesti il nodo con F minima
		//ma solo quello con VICINO con F minima, che poi è quello con H minima
		//qOpenList.clear();
		if (*pCurrNode != *pEndNode) 
		{
			//add the almost 4 neighboars
			CreateNodeAdj(pCurrNode);

			//add neighboars to open list
			std::list<Node15*>::const_iterator it = pCurrNode->m_aAdj.begin();
			for (; it != pCurrNode->m_aAdj.end(); ++it)
			{
				AddNodeToOpenList(pCurrNode, *it);
			}
		}
		else
		{
			std::cout << "\nSolution Find\n";
			//troppo tardi per scriverlo per bene
			std::list<Node15*> solution;
			Node15* n = new Node15{ *pCurrNode };
			while (n->m_pParent != nullptr)
			{
				solution.push_front(n->m_pParent);
				n = n->m_pParent;
			}

			std::list<Node15*>::const_iterator it = solution.begin();
			for (; it != solution.end(); ++it)
			{
				pCurrNode = *it;
				Sleep(400);
			}
			return;
		}
		//Lo sleep lo mettiamo dopo: faremo il print alla fine di tutto.
		//Sleep(200);
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
			//è *it che dobbiamo aggiornare, dato che è quello nella open list 
			if ((*it)->m_iG > pParent->m_iG + 1)
			{
				(*it)->m_pParent = pParent;
				(*it)->m_iG = pParent->m_iG + 1;
				(*it)->m_iF = (*it)->m_iG + (*it)->m_iH;
				return;
			}
		}
	}

	//valorize the node value for the first time
	ComputeNodeHeuristic(pNode);

	//pNode->m_pParent = pParent; //Lo facciamo già nel costruttore
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
