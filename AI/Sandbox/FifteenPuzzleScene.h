#pragma once

#include "IScene.h"
#include <algorithm>
#include <sstream>
#include "FontManager.h"
#include "AStar15.h"

class FifteenPuzzleScene : public IScene
{
private:
	AStar15 *m_pAS15;
	sf::RectangleShape* m_aoQuads;
	sf::Text* m_aoTexts;

public:
	sf::Thread m_Thread{ &FifteenPuzzleScene::Launch, this };
	void Launch();

	FifteenPuzzleScene();


    virtual void OnIdle();
    virtual void OnDraw(sf::RenderWindow&);

	virtual ~FifteenPuzzleScene();
};