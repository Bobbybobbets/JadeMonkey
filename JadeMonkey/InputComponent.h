#include "Game.h"
#include "GameComponent.h"
#include "GameEntity.h"
#include "BEntityComponent.h"

class InputComponent : public EntityComponent
{
public:
	InputComponent(Game* game);
};