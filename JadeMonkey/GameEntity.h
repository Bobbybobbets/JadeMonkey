#pragma once
#include "Game.h"
#include "GameComponent.h"

class GameEntity : public GameComponent
{
public:
	~GameEntity(void);
	GameEntity(Game* game);
	virtual int Initialize() override;
	virtual int Update(long time) override;
	D3DXVECTOR3 getPosition(void);
	D3DXVECTOR3 getDirection(void);
	D3DXVECTOR3 getRotation(void);
	D3DXVECTOR3 getScale(void);

protected:
	D3DXVECTOR3 _position;	// position of object
	D3DXVECTOR3 _direction;	// direction of object
	D3DXVECTOR3 _rotation;	// angle of rotation of the object
	D3DXVECTOR3 _scale;		// scale of the object
	int numVtx;
	int numQuads;
	int numTriangles;
};