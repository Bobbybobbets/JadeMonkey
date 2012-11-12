#include "Game.h"
#include "GameComponent.h"
#include "GameEntity.h"
#include "EntityComponent.h"

class InputComponent : public EntityComponent
{
public:
	InputComponent(Game* game);
};