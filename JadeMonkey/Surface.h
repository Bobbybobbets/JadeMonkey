#pragma once

#include "IDrawable.h"
#include "GameEntity.h"
#include "Game.h"

class Surface : public GameEntity, public IDrawable {

public:
	Surface(int height , int width, Game *game); // Maybe add in the textures here too
	~Surface();

	virtual int Initialize();
	virtual int Update(long time);
	virtual int Draw(long time);
	virtual int LoadContent();
};