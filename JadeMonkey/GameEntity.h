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
	void setPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 getDirection(void);
	void setDirection(D3DXVECTOR3 direction);
	D3DXVECTOR3 getRotation(void);
	void setRotation(D3DXVECTOR3 rotation);
	D3DXVECTOR3 getScale(void);
	void setScale(D3DXVECTOR3 scale);

protected:
	D3DXVECTOR3 _position;	// position of object
	D3DXVECTOR3 _direction;	// direction of object
	D3DXVECTOR3 _rotation;	// angle of rotation of the object
	D3DXVECTOR3 _scale;		// scale of the object
	int numVtx;
	int numQuads;
	int numTriangles;
};