#include "MinerScene.h"
#include <Windows.h>

MinerScene::MinerScene()
{
	m_pMiner = new Miner(0.8f,100,10);

	m_RenderMiner = new sf::CircleShape(20);

	const sf::Font* font = FontManager::Istance()->GetFont(FontEnum::Font_Consola);
	m_aoTexts = new sf::Text[6];


	for (int i = 0; i < 6; ++i)
	{
		m_aoTexts[i].setFont(*font);
		m_aoTexts[i].setCharacterSize(30);
		m_aoTexts[i].setFillColor(mk_aoColors[i]);
		m_aoTexts[i].setPosition(400,50 * i);
	}

	m_aoTexts[0].setString("HOME");
	m_aoTexts[1].setString("TRAVEL");
	m_aoTexts[2].setString("MINE");
	m_aoTexts[3].setString("SLEEP");

	m_Thread.launch();
}

MinerScene::~MinerScene()
{
    
}

void MinerScene::Launch()
{
	while (true)
	{
		m_pMiner->Update();
		Sleep(100);
	}
}

void MinerScene::OnIdle()
{
	
}

void MinerScene::OnDraw(sf::RenderWindow& renderWindow)
{	
	m_RenderMiner->setFillColor(mk_aoColors[m_pMiner->currState]);
	renderWindow.draw(*m_RenderMiner);
	for (int i = 0; i < 4; ++i)
	{
		renderWindow.draw(m_aoTexts[i]);
	}

	m_aoTexts[4].setString("GOLD: " + std::to_string(m_pMiner->GetGold()));
	m_aoTexts[5].setString("TIREDNESS: " + std::to_string(m_pMiner->GetTired()));
	renderWindow.draw(m_aoTexts[4]);
	renderWindow.draw(m_aoTexts[5]);

}





