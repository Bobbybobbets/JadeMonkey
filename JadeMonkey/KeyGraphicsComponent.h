#pragma once

#include "GraphicsComponent.h"
#include "PlayerComponent.h"
#include "KeyPartComponent.h"
#include "TexturedGraphicsComponent.h"

class KeyGraphicsComponent : public TexturedGraphicsComponent
{
private:
	int height;
	PlayerComponent *_player;
	KeyPartComponent *_keyPart;
public:
	KeyGraphicsComponent(int dx, int dy, PlayerComponent *player,  KeyPartComponent *keyPart, Game* game, GameEntity* entity);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	virtual void setupRender() override;

	virtual string GetName(void) override;

	int getHeight();

protected:
	virtual void loadMesh(void) override;
	virtual void loadTexture(void) override;

};