#include "TexturedGraphicsComponent.h"

TexturedGraphicsComponent::TexturedGraphicsComponent(Game* game, GameEntity* entity)
	: GraphicsComponent(game, entity)
{
}

void TexturedGraphicsComponent::Initialize(void)
{
	GraphicsComponent::Initialize();
	this->loadTexture();
}

void TexturedGraphicsComponent::setupRender()
{
	IDirect3DDevice9* d3ddev = this->_game->getGraphicsDevice();
	
	GraphicsComponent::setupRender();

	d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	d3ddev->SetTexture(0, this->_texture);
	d3ddev->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	d3ddev->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	d3ddev->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}
