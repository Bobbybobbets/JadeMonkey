#include "EntityFactory.h"
#include "PlayerComponent.h"

class MainEntityFactory : public EntityFactory
{
public:
	MainEntityFactory(Game* game);
	virtual GameEntitiesContainer GetContainer() override;
private:
	GameEntitiesContainer AddFloor(int numCols, int num, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player);
	GameEntitiesContainer AddWall(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player, bool xWall);

};