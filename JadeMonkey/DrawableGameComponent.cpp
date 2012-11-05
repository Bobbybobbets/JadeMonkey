#include "DrawableGameComponent.h"

DrawableGameComponent::DrawableGameComponent(Game* game) : GameComponent(game)
{
}

DrawableGameComponent::~DrawableGameComponent()
{
	GameComponent.~GameComponent();
}

