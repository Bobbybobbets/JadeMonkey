#include "PointLightComponent.h"
#include "GameEntity.h"

int PointLightComponent::_lightCounter = 0;

PointLightComponent::PointLightComponent(Game* game, GameEntity* entity, D3DXCOLOR color, float range)
	: BEntityComponent(game, entity)
{
	this->_lightNumber = PointLightComponent::_lightCounter++;
	this->_color = color;
	this->_range = range;
}

void PointLightComponent::Initialize(void)
{
	IDirect3DDevice9* d3ddev = this->_game->getGraphicsDevice();
	ZeroMemory(&this->_light, sizeof(this->_light));

	this->_light.Type = D3DLIGHT_POINT;
	this->_light.Diffuse = this->_color;
	this->_light.Position = this->_entity->getPosition();
	this->_light.Range = this->_range;

	d3ddev->SetLight(this->_lightNumber, &this->_light);
	d3ddev->LightEnable(this->_lightNumber, TRUE);
}

void PointLightComponent::Update(GameEntity* entity, long time)
{
	IDirect3DDevice9* d3ddev = this->_game->getGraphicsDevice();

	this->_light.Position = this->_entity->getPosition();

	d3ddev->SetLight(this->_lightNumber, &this->_light);
}