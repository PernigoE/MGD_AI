#pragma once

#include "IScene.h"


class MinerScene : public IScene
{
public:

	MinerScene();
	virtual ~MinerScene();
    
	virtual void OnIdle();
	virtual void OnDraw(sf::RenderWindow& renderWindow);
};

