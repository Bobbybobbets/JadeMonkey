#include "GameComponent.h"

class GameMap : public GameComponent
{
public:

	~GameMap();
	GameMap();
	virtual int Initialize();
	virtual int Update();

}