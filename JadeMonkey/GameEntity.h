#pragma once

#include "Enums.h"
#include "Game.h"
#include "DrawableGameComponent.h"
#include "BEntityComponent.h"
#include <vector>
#include "SkillComponent.h"

//#include "CollisionComponent.h"

using namespace std;
class CollisionComponent;
class GraphicsComponent;
class GameEntity : public DrawableGameComponent
{
public:
	~GameEntity(void);
	GameEntity(Game* game);
	GameEntity(Game* game, D3DXVECTOR3 size);
	void AddComponent(BEntityComponent* component);
	void AddComponent(BEntityComponent* component, vector<BEntityComponent*> dependencies);
	void AddGraphicsComponent(GraphicsComponent* component);
	void AddSkillComponent(SkillComponent* component);
	void AddDrawableComponent(BDrawableEntityComponent* drawableComponent);
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
	D3DXVECTOR3 getSize(void);
	void setSize(D3DXVECTOR3 size);
	float getSpeed(void);
	void setSpeed(float speed);
	int getHeight(void);
	void setHeight(int height);
	int getStepHeight(void);
	void setStepHeight(int stepHeight);
	float getVelocity(void);
	void setVelocity(float velocity);
	int getLife(void);
	void setLife(int life);
	void reduceLife(int amount);
	bool IsVisible(void);
	bool IsActive();
	void SetStatus(bool active);
	EntityType GetType(void);
	void SetType(EntityType type);
	BDrawableEntityComponent* getGraphicsComponent();
	vector<CollisionComponent*> getCollisionComponents();
	void AddCollisionComponent(CollisionComponent* component);
	

protected:
	D3DXVECTOR3 _position;	// position of object
	D3DXVECTOR3 _positionBuffer;
	D3DXVECTOR3 _direction;	// direction of object
	D3DXVECTOR3 _rotation;	// angle of rotation of the object
	D3DXVECTOR3 _scale;
	D3DXVECTOR3 _size;
	int _life;
	float _velocity;
	int _height;
	int _stepHeight;
	float _speed;
	int numVtx;
	int numQuads;
	int numTriangles;
	bool _active;
	EntityType _type;
	vector<BEntityComponent*> _components;
	vector<BDrawableEntityComponent*> _graphicsComponents;
	vector<SkillComponent*> _skillComponents;
	vector<CollisionComponent*> _collisionComponents;

	bool _visible;
};
