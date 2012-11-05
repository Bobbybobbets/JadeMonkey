#pragma once
#include "IDrawable.h"
#include "GameComponent.h"

class DrawableGameComponent : public GameComponent, public IDrawable
{
public:
	~DrawableGameComponent();
	DrawableGameComponent(Game* game);
	virtual int Draw(long time) = 0;
};