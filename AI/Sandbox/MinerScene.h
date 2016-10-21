#pragma once

#include "IScene.h"
#include "Miner.h"
#include "FontManager.h"

class MinerScene : public IScene
{
private:
	Miner* m_pMiner;
	sf::CircleShape* m_RenderMiner;
	sf::Text* m_aoTexts;
	const sf::Color mk_aoColors[6]{ sf::Color::White, sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color::Black , sf::Color::Black };

public:
	MinerScene();
	virtual ~MinerScene();

	sf::Thread m_Thread{ &MinerScene::Launch, this };
	void Launch();

	virtual void OnIdle();
	virtual void OnDraw(sf::RenderWindow& renderWindow);
};

