#pragma once
#include "GameComponent.h"
#include "IDrawable.h"

class Game;

class DrawableGameComponent : public GameComponent, public IDrawable
{
public:
	~DrawableGameComponent();
	DrawableGameComponent(Game *game);
	virtual int Initialize(void) = 0;
	virtual int Update(long time) = 0;
	virtual int Draw(long time) = 0;
};