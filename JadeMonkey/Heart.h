#pragma once

#include "GameEntity.h"
#include "jade_util.h"

class Heart: public GameEntity
{
public:
	Heart(Game* game, D3DXVECTOR3 position);
	~Heart();

	virtual int Initialize() override;
	virtual int Draw(long time) override;

private:
	void LoadSprite();

	D3DXVECTOR3 _position;
	LPD3DXSPRITE _heart;
	LPDIRECT3DTEXTURE9 _heartTexture;
};	