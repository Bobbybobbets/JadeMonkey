#pragma once

#include "GameComponent.h"
#include "IDrawable.h"
#include "DrawableGameComponent.h"

class Game;

class DrawableGameComponent : /*public GameComponent , */public IDrawable
{
public:
	~DrawableGameComponent();
	DrawableGameComponent(Game *game);
	virtual int Draw(long time) = 0;
};