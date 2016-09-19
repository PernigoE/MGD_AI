#pragma once

#include "AStar.h"
#include "IScene.h"
#include "FontManager.h"
#include <assert.h>
#include <vector>
#include <list>
#include <time.h>
#include <sstream>



class AStarScene : public IScene
{
private:
	AStar *m_pAlg;
	sf::RectangleShape* m_aoQuads;
	sf::Text* m_aoTexts;
	const sf::Color mk_aoColors[5]{ sf::Color::White, sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Yellow };

public:
	sf::Thread m_Thread{&AStarScene::Launch, this};
    
	AStarScene();
    
	void Launch();

	virtual void OnIdle(void);
	virtual void OnDraw(sf::RenderWindow&);
    
	virtual ~AStarScene(void);

};


