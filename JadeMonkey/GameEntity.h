#pragma once
#include "Game.h"
#include "DrawableGameComponent.h"
#include "BEntityComponent.h"
#include <vector>

using namespace std;

class GameEntity : public DrawableGameComponent
{
public:
	~GameEntity(void);
	GameEntity(Game* game);
	void AddComponent(BEntityComponent* component);
	void AddComponent(BEntityComponent* component, vector<BEntityComponent*> dependencies);
	void AddGraphicsComponent(BEntityComponent* component);
	virtual int Initialize() override;
	virtual int Update(long time) override;
	virtual int Draw(long time) override;
	D3DXVECTOR3 getPosition(void);
	D3DXVECTOR3 getPositionBuffer(void);
	void setPosition(D3DXVECTOR3 position);
	D3DXVECTOR3 getDirection(void);
	void setDirection(D3DXVECTOR3 direction);
	D3DXVECTOR3 getRotation(void);
	void setRotation(D3DXVECTOR3 rotation);
	D3DXVECTOR3 getScale(void);
	void setScale(D3DXVECTOR3 scale);
	bool IsVisible(void);

protected:
	D3DXVECTOR3 _position;	// position of object
	D3DXVECTOR3 _positionBuffer;
	D3DXVECTOR3 _direction;	// direction of object
	D3DXVECTOR3 _rotation;	// angle of rotation of the object
	D3DXVECTOR3 _scale;		// scale of the object
	int numVtx;
	int numQuads;
	int numTriangles;
	vector<BEntityComponent*> _components;
	vector<BEntityComponent*> _graphicsComponents;
	bool _visible;
};