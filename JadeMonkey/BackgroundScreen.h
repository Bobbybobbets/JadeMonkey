#pragma once
#include "GameEntity.h"

class BackgroundScreen: public GameEntity
{
public:
	BackgroundScreen(Game *game);


	virtual int Initialize() override;
	virtual int Draw(long time) override;
	void LoadSprite(char *file);
private:
	void LoadSprite();

	D3DXVECTOR3 _position;
	LPD3DXSPRITE _background;
	LPDIRECT3DTEXTURE9 _backgroundTexture;

};