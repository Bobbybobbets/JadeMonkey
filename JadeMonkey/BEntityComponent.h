#pragma once
#include "Game.h"
#include <string>
//#include "GameEntity.h"

using namespace std;

class GameEntity;
class BEntityComponent
{
public:
	BEntityComponent(Game* game, GameEntity* entity);
	~BEntityComponent(void);
	virtual void Initialize(void);
	virtual void Update(GameEntity* entity, long time);
	virtual string GetName(void);

	GameEntity* getEntity();

	virtual int getNumRows(){return 0;};
	virtual int getNumCols(){return 0;};
	virtual float getDx(){return 0;};
	virtual float getDy(){return 0;};
	virtual float getDz(){return 0;};
protected:
	Game* _game;
	GameEntity* _entity;
};