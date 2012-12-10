#pragma once
#include "BEntityComponent.h"
#include <d3dx9.h>

class GameEntity;

class PointLightComponent : public BEntityComponent
{
public:
	PointLightComponent(Game* game, GameEntity* entity, D3DXCOLOR color, float range);
	virtual void Initialize(void);
	virtual void Update(GameEntity* entity, long time);

protected:
	D3DXCOLOR _color;
	float _range;
	D3DLIGHT9 _light;
	int _lightNumber;
	static int _lightCounter;
};