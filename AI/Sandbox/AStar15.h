#pragma once

#include <SFML\System.hpp>
#include <iostream>
#include <list>
#include "Node15.h"

class AStar15
{
public:
	AStar15();
	~AStar15();

	Node15* GetCurrNode();

    void Run();

private:
    Node15* pStartNode;
	Node15* pEndNode;
	Node15* pCurrNode;

    
	int GetZeroPos(Node15*);

	//function add adj at passed node and control if is not its parent
	//possono essere scritte meglio
	void AdjZeroUp(Node15*);
	void AdjZeroDown(Node15*);
	void AdjZeroLeft(Node15*);
	void AdjZeroRight(Node15*);

	//provo a riscrivere le mossi in questo modo. Mi � utile anche per lo start node.
	enum MOVES
	{
		UP = -4,
		DOWN = 4,
		LEFT = -1,
		RIGHT = 1
	};

	const MOVES Moves[4] = { UP, DOWN, LEFT, RIGHT };
	Node15* NeighbourByMove(Node15*, MOVES);

	////////////////////////////////////////////

    void CreateGraph();
    void CreateGraphAdjs();
	void CreateNodeAdj(Node15* node);

    
    void ComputeGraphHeuristics();
    void ComputeNodeHeuristic(Node15* pNode);
    
    void Clean();
    
    void Search();
	Node15* VisitNode();
    void AddNodeToOpenList(Node15* pParent, Node15* pNode);

	std::list<Node15*> qOpenList;
	std::list<Node15*> qClosedList;

};