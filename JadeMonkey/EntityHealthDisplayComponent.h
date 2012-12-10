#pragma once
#include "BillboardDisplayComponent.h"

class EntityHealthDisplayComponent : public BillboardDisplayComponent
{
public:
	EntityHealthDisplayComponent(Game* game, GameEntity* entity, GameEntity* player);
	virtual void Draw(long time) override;

protected:
	LPDIRECT3DTEXTURE9 _texture2;
	virtual void setupRender(void) override;
	virtual void loadMesh(void) override;
	virtual void loadTexture(void) override;
};
