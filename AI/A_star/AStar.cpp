#include "AStar.h"
#include <algorithm>

void AStar::CreateGraph()
{
	for (int iRow = 0; iRow < yMax; ++iRow)
	{
		for (int iCol = 0; iCol < xMax; ++iCol)
		{
			tRoot[iRow*xMax + iCol] = new Node();
			tRoot[iRow*xMax + iCol]->m_iRow = iRow;
			tRoot[iRow*xMax + iCol]->m_iCol = iCol;
		}
	}

	CreateGraphAdjs();
}

void AStar::CreateGraphAdjs()
{
	for (int iRow = 0; iRow < yMax; ++iRow)
	{
		for (int iCol = 0; iCol < xMax; ++iCol)
		{
			CreateNodeAdj(iRow, iCol);
		}
	}
}

void AStar::CreateNodeAdj(const int iRow, const int iCol)
{
	//Credo si possa migliorare. Ma come era prima aveva un problema: 
	//all'ultima colonna della riga metteva come vicino la prima colonna della riga.
	//Inoltre si deve stare attenti a non inserire lo stesso nodo, altrimenti il costo sarebbe 0.
	for (int iAdjRow = std::max(iRow - 1, 0); iAdjRow < std::min(iRow + 2, yMax); ++iAdjRow)
	{
		for (int iAdjCol = std::max(iCol - 1, 0); iAdjCol < std::min(iCol + 2, xMax); ++iAdjCol)
		{
			if (iAdjCol != iCol || iAdjRow != iRow) {
				int iWeight = abs(iAdjRow - iRow) + abs(iAdjCol - iCol);
				tRoot[iRow*xMax + iCol]->m_aAdj.insert(std::make_pair(tRoot[iAdjRow*xMax + iAdjCol], iWeight));
			}
		}
	}
}

void AStar::ComputeGraphHeuristics()
{
	for (int index = 0; index < xMax * yMax; ++index)
	{
		ComputeNodeHeuristic(tRoot[index]);
	}
}

void AStar::ComputeNodeHeuristic(Node* pNode)
{
	int iRow = iEndNode%xMax;
	int iCol = iEndNode / xMax;

	pNode->m_iH = abs(pNode->m_iRow - iRow) + abs(pNode->m_iCol - iCol);
}

void AStar::Clean()
{
	qOpenList.clear();

	for (int i = 0; i < xMax * yMax; ++i)
	{
		delete tRoot[i];
	}
}

void AStar::Search()
{
	qOpenList.push_back(tRoot[iStartNode]);

	Node* pCurrNode;
	while (!qOpenList.empty())
	{
		pCurrNode = VisitNode();
		if (pCurrNode != tRoot[iEndNode]) {
			std::map<Node*, int>::const_iterator it = pCurrNode->m_aAdj.begin();
			for (; it != pCurrNode->m_aAdj.end(); ++it)
			{
				AddNodeToOpenList(pCurrNode, it->first);
			}
		}
		else
		{
			PrintPath(pCurrNode);
			return;
		}
	}

	std::cout << "No Path" << std::endl;
}

Node* AStar::VisitNode()
{
	Node* minGNode = qOpenList.front();
	std::list<Node*>::iterator index = qOpenList.begin();
	for (std::list<Node*>::iterator it = ++qOpenList.begin(); it != qOpenList.end(); ++it)
	{
		if (minGNode->m_iF > (*it)->m_iF)
		{
			minGNode = (*it);
			index = it;
		}
	}
	minGNode->m_eState = NodeState::IN_CLOSED;
	qOpenList.erase(index);
	return minGNode;
}

//control state, controll F
void AStar::AddNodeToOpenList(Node* pParent, Node* pNode)
{
	if (pNode->m_eState == NodeState::IN_CLOSED)
	{
		return;
	}
	else if (pNode->m_eState == NodeState::NOT_VISITED)
	{
		//Se un nodo non è mai stato visitato lo inserisco direttamente nella lista
		//calcolando anche, per la prima volta, la sua euristica.
		ComputeNodeHeuristic(pNode);

		pNode->m_eState = NodeState::IN_OPEN;
		pNode->m_pParent = pParent;
		pNode->m_iG = pParent->m_iG + pParent->m_aAdj[pNode];
		pNode->m_iF = pNode->m_iG + pNode->m_iH;

		qOpenList.push_back(pNode);
	}
	else if (pNode->m_eState == NodeState::IN_OPEN)
	{
		//Se un nodo è nella lista di nodi aperti allora controllo se il suo costo
		//è maggiore di quello che avrebbe attualmente. Nel caso lo aggiorno
		if (pNode->m_iG > pParent->m_iG + pParent->m_aAdj[pNode])
		{
			pNode->m_pParent = pParent;
			pNode->m_iG = pParent->m_iG + pParent->m_aAdj[pNode];
			pNode->m_iF = pNode->m_iG + pNode->m_iH;
		}
	}
}

void AStar::PrintPath(Node* pNode) const
{
	//La stampa del path avviene all'incontrario.
	while (pNode != nullptr)
	{
		std::cout << "Nodo: " << pNode->m_iRow << ", " << pNode->m_iCol << std::endl;

		pNode = pNode->m_pParent;
	}
}

void AStar::Run() {
	CreateGraph();

	Search();

	std::system("Pause");
	Clean();
}