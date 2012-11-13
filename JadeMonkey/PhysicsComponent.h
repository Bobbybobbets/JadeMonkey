#include "BEntityComponent.h"
#include "GameEntity.h"

class PhysicsComponent : public BEntityComponent
{
public:
	PhysicsComponent(Game* game, GameEntity* entity);
	void Initialize(void) override;
	void Update(GameEntity* entity, long time) override;

private:
	D3DXVECTOR3 _velocity;
	D3DXVECTOR3 _acceleration;
};