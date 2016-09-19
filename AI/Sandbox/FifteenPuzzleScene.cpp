#include "FifteenPuzzleScene.h"

FifteenPuzzleScene::FifteenPuzzleScene()
{
	m_pAS15 = new AStar15();

	m_aoQuads = new sf::RectangleShape[16];
	m_aoTexts = new sf::Text[17];
	const sf::Font* font = FontManager::Istance()->GetFont(FontEnum::Font_Consola);

	sf::Vector2f pos = { 50,50 };
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			int index = i * 4 + j;
			m_aoQuads[index] = sf::RectangleShape({ 100,100 });
			m_aoQuads[index].setPosition(pos);
			m_aoQuads[index].setFillColor(sf::Color::White);

			m_aoTexts[index].setFont(*font);
			m_aoTexts[index].setCharacterSize(50);
			m_aoTexts[index].setFillColor(sf::Color::Black);
			m_aoTexts[index].setPosition(pos + sf::Vector2f{25,25});

			pos.x += 120;
		}
		pos.x -= 120 * 4;
		pos.y += 120;
	}
	
	m_aoTexts[16].setFont(*font);
	m_aoTexts[16].setPosition({ 600,200 });
	m_aoTexts[16].setCharacterSize(25);
	m_aoTexts[16].setFillColor(sf::Color::Black);


	m_Thread.launch();
}

void FifteenPuzzleScene::Launch()
{
	m_pAS15->Run();
}

FifteenPuzzleScene::~FifteenPuzzleScene()
{
	m_Thread.terminate();
	delete m_pAS15;
	delete[] m_aoQuads;
	delete[] m_aoTexts;
}

void FifteenPuzzleScene::OnIdle()
{

}

void FifteenPuzzleScene::OnDraw(sf::RenderWindow& renderWindow)
{	
	Node15* n = m_pAS15->GetCurrNode();
	for (int i = 0; i < 16; ++i)
	{
		if (n->State[i] != 0)
		{
			m_aoTexts[i].setString(std::to_string(n->State[i]));
			renderWindow.draw(m_aoQuads[i]);
			renderWindow.draw(m_aoTexts[i]);
		}
	}
	std::string s = "Distance from solution = " + std::to_string(n->m_iH);
	m_aoTexts[16].setString(s);
	renderWindow.draw(m_aoTexts[16]);
}