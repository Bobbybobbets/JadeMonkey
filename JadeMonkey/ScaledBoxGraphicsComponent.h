#pragma once
#include "GraphicsComponent.h"

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

class ScaledBoxGraphicsComponent : public GraphicsComponent
{
public:
	ScaledBoxGraphicsComponent(Game* game, GameEntity* entity, D3DCOLOR color);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	virtual void Draw(long time) override;
	virtual string GetName(void) override;

protected:
	virtual void loadMesh(void) override;

private:
	D3DCOLOR _color;
	IDirect3DVertexBuffer9* v_buffer;
	IDirect3DIndexBuffer9* i_buffer;

};