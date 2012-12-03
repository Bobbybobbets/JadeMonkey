#pragma once
#include "BEntityComponent.h"
#include <d3dx9.h>
#include "GameEntity.h"


class AIControllerComponent : public BEntityComponent
{
public:
	AIControllerComponent(Game* game, GameEntity* entity);
	void Update(GameEntity* entity, long time) override;
	void MoveTo(D3DXVECTOR3 position);

protected:
	D3DXVECTOR3 _moveToPosition;
	bool _moving;
};
