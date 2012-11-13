#pragma once
#include "CollisionComponent.h"
#include <vector>

using namespace std;

class CuboidPrism
{
public:
	CuboidPrism(vector<D3DXVECTOR3> vertices);
	float MinX(void);
	float MaxX(void);
	float MinY(void);
	float MaxY(void);
	float MinZ(void);
	float MaxZ(void);

	vector<D3DXVECTOR3> Vertices;
	
};

class CuboidCollisionComponent : public CollisionComponent
{
public:
	CuboidCollisionComponent(Game* game, GameEntity* entity, CuboidPrism* boundingBox, bool active);
	virtual void Initialize(void) override;
	virtual void Update(GameEntity* entity, long time) override;
	virtual string GetName(void) override;
	D3DXVECTOR3 Position(void);

protected:
	static vector<CuboidPrism*> _globalBoundingBoxes;
	bool _active;
	CuboidPrism* _boundingBox;
	D3DXVECTOR3 _position;
};

