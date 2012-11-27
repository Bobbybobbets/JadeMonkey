#pragma once

#include "BEntityComponent.h"

class KeyPartComponent: public BEntityComponent
{
public:
	KeyPartComponent(Game *game, GameEntity *entity, int keyNumber, D3DXVECTOR3 position);
	~KeyPartComponent();

	virtual void Initialize(void) override;

	bool checkPickup(D3DXVECTOR3 position);	 
	bool getRetrieved();

private:
	int keyNumber;
	D3DXVECTOR3 _position;
	bool retrieved;

	static float pickupDistance;
};