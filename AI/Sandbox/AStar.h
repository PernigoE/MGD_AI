#pragma once

#include <SFML\System.hpp>
#include <iostream>
#include <list>
#include "Node.h"

class AStar
{
public:
	AStar();

    void Run();

	int GetXSize() const;
	int GetYSize() const;
	
	Node& GetNode(int i);

private:
    const static int xMax = 10;
    const static int yMax = 10;
    const static int iStartNode = 0;
    const static int iEndNode = 65;
    

    void CreateGraph();
    void CreateGraphAdjs();
    void CreateNodeAdj(const int iRow, const int iCol);
    
    void ComputeGraphHeuristics();
    void ComputeNodeHeuristic(Node* pNode);
    
    void Clean();
    
    void Search();
    Node* VisitNode();
    void AddNodeToOpenList(Node* pParent, Node* pNode);
    
    void PrintPath(Node* pNode) const;
    
    Node* tRoot[xMax * yMax];
    
    std::list<Node*> qOpenList;

};
