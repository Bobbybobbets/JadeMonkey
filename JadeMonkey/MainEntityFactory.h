#include "EntityFactory.h"

class MainEntityFactory : public EntityFactory
{
public:
	MainEntityFactory(Game* game);
	virtual GameEntitiesContainer GetContainer() override;
};