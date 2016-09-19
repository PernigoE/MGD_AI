#include "AStarScene.h"
#include <string>

AStarScene::AStarScene()
{
	m_pAlg = new AStar();
	int xSize = m_pAlg->GetXSize();
	int ySize = m_pAlg->GetYSize();

	m_aoQuads = new sf::RectangleShape[xSize * ySize];

	const sf::Font* font = FontManager::Istance()->GetFont(FontEnum::Font_Consola);
	m_aoTexts = new sf::Text[xSize * ySize];

	sf::Vector2f pos = { 50,50 };
	for (int iRow = 0; iRow < ySize; ++iRow)
	{
		for (int iCol = 0; iCol < xSize; ++iCol)
		{
			int index = iRow*xSize + iCol;
			m_aoQuads[index] = sf::RectangleShape({40,40});
			m_aoQuads[index].setPosition(pos);

			m_aoTexts[index].setFont(*font);
			m_aoTexts[index].setCharacterSize(10);
			m_aoTexts[index].setFillColor(sf::Color::Black);
			m_aoTexts[index].setPosition(pos);
			pos.x += 50;
		}
		pos.x -= 500;
		pos.y += 50;
	}
	
	m_Thread.launch();

}

void AStarScene::Launch()
{
	m_pAlg->Run();
}


AStarScene::~AStarScene()
{
	delete m_pAlg;
	delete[] m_aoQuads;
	delete[] m_aoTexts;
}

void AStarScene::OnIdle()
{
	
}

void AStarScene::OnDraw(sf::RenderWindow& renderWindow)
{
	int size = m_pAlg->GetXSize() * m_pAlg->GetYSize();
	
	for (int i = 0; i < size; ++i)
	{
		Node n = m_pAlg->GetNode(i);
		std::string s = std::to_string(n.m_iG).substr(0,3) + "+" + std::to_string(n.m_iH).substr(0, 3);		

		m_aoQuads[i].setFillColor(mk_aoColors[n.m_eState]);
		m_aoTexts[i].setString(s);
		renderWindow.draw(m_aoQuads[i]);
		renderWindow.draw(m_aoTexts[i]);
	}
}
