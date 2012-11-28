#include "EntityFactory.h"
#include "PlayerComponent.h"

class MainEntityFactory : public EntityFactory
{
public:
	MainEntityFactory();
	virtual GameEntitiesContainer GetContainer(Game* game) override;

};