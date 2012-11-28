#pragma once

#include "BEntityComponent.h"
#include "PlayerComponent.h"

class KeyPartComponent: public BEntityComponent
{
public:
	KeyPartComponent(Game *game, GameEntity *entity, PlayerComponent *player, int keyNumber, D3DXVECTOR3 position);
	~KeyPartComponent();

	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;

	bool checkPickup(D3DXVECTOR3 position);	 
	bool getRetrieved();

private:
	int keyNumber;
	D3DXVECTOR3 _position;
	bool retrieved;
	PlayerComponent *_player;

	static float keyWidth;
};