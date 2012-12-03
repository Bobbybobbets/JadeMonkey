#include "EntityFactory.h"
#include "PlayerComponent.h"
#include "CameraComponent.h"


class MainEntityFactory : public EntityFactory
{
private:
	DoorUseComponent* AddDoor(int numCols, int numRows, D3DXVECTOR3 position, GameEntitiesContainer gc, PlayerComponent *player, bool xWall, CameraComponent *camera);
public:
	MainEntityFactory();
	virtual GameEntitiesContainer GetContainer(Game* game) override;

};