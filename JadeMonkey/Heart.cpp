#include "Heart.h"
#include "RessourceManager.h"

Heart::Heart(Game *game, D3DXVECTOR3 position): GameEntity(game)
{
	_position = position;
	Initialize();
}

Heart::~Heart()
{

}

int Heart::Initialize()
{
	LoadSprite();
	D3DXCreateSprite(_game->getGraphicsDevice(), &_heart);

	return 0;
}
int Heart::Draw(long time)
{
	D3DXMATRIX mat;

	_heart->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXVECTOR2 spriteCentre = D3DXVECTOR2(16.0f,14.0f);
	D3DXVECTOR2 translation = D3DXVECTOR2(_position.x, _position.y);
	float rotation = 0;
	D3DXVECTOR2 scaling = D3DXVECTOR2(1.0,1.0);	

	D3DXMatrixTransformation2D(&mat,NULL,0.0,&scaling,&spriteCentre,rotation,&translation);

	_heart->SetTransform(&mat);
	_heart->Draw(_heartTexture, NULL, NULL, NULL, 0xFFFFFFFF);	

	_heart->End();

	return 0;
}

void Heart::LoadSprite()
{
	if( _game->getGraphicsDevice() != 0)
		this->_heartTexture = RessourceManager::GetTexture(_game->getGraphicsDevice(), "Textures/heart.png");
}