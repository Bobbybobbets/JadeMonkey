#pragma once
#include "GraphicsComponent.h"

class TexturedGraphicsComponent : public GraphicsComponent
{
public:
	TexturedGraphicsComponent(Game* game, GameEntity* entity);
	virtual void Initialize(void) override;

protected:
	LPDIRECT3DTEXTURE9 _texture;
	virtual void loadMesh(void) = 0;
	virtual void loadTexture(void) = 0;
	virtual void setupRender(void);
};