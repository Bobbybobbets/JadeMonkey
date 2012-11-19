#pragma once


#include "Game.h"
#include "DrawableGameComponent.h"
#include "BEntityComponent.h"
#include <vector>

//#include "CollisionComponent.h"

using namespace std;
class CollisionComponent;
class GraphicsComponent;
class GameEntity : public DrawableGameComponent
{
public:
	~GameEntity(void);
	GameEntity(Game* game);
	void AddComponent(BEntityComponent* component);
	void AddComponent(BEntityComponent* component, vector<BEntityComponent*> dependencies);
	void AddGraphicsComponent(GraphicsComponent* component);
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
	GraphicsComponent* getGraphicsComponent();
	vector<CollisionComponent*> getCollisionComponents();
	void AddCollisionComponent(CollisionComponent* component);
	vector<GraphicsComponent*> _graphicsComponents;

protected:
	D3DXVECTOR3 _position;	// position of object
	D3DXVECTOR3 _positionBuffer;
	D3DXVECTOR3 _direction;	// direction of object
	D3DXVECTOR3 _rotation;	// angle of rotation of the object
	D3DXVECTOR3 _scale;
	int numVtx;
	int numQuads;
	int numTriangles;
	vector<BEntityComponent*> _components;

	vector<CollisionComponent*> _collisionComponents;

	bool _visible;
};
