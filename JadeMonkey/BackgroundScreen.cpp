#include "BackgroundScreen.h"
#include "RessourceManager.h"

BackgroundScreen::BackgroundScreen(Game *game) : GameEntity(game)
{
	Initialize();
}

int BackgroundScreen::Initialize()
{
	LoadSprite();
	D3DXCreateSprite(_game->getGraphicsDevice(), &_background);

	return 0;
}
int BackgroundScreen::Draw(long time)
{
	D3DXMATRIX mat;

	_background->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR2 spriteCentre = D3DXVECTOR2(300,200);
	D3DXVECTOR2 translation = D3DXVECTOR2(0,0);
	float rotation = 0;
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.2,1.6);	

	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,rotation,&translation);


	_background->SetTransform(&mat);
	_background->Draw(_backgroundTexture, NULL, NULL, NULL, 0xFFFFFFFF);	

	_background->End();

	return 0;
}

void BackgroundScreen::LoadSprite()
{
	if( _game->getGraphicsDevice() != 0)
		this->_backgroundTexture = RessourceManager::GetTexture(_game->getGraphicsDevice(), "Textures/forest-temple-oot2.png");
}

void BackgroundScreen::LoadSprite(char *file)
{
	if( _game->getGraphicsDevice() != 0)
		this->_backgroundTexture = RessourceManager::GetTexture(_game->getGraphicsDevice(), file);
}