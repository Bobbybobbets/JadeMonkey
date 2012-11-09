#pragma once

#include "IDrawable.h"
#include "GameEntity.h"
#include "Game.h"

#define NUSS_SHADERS 1

struct meshVertex {
	D3DXVECTOR3 pos;
    DWORD color;        // The vertex color

};
#ifndef NUSS_SHADERS
#define MESH_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#endif



class meshSurface: public GameEntity, public IDrawable {

public:
	meshSurface(int numRows, int numCols, float dx, float dz, Game *game); // Maybe add in the textures here too
	~meshSurface();

	void setScale(float x , float y, float z);
	
	virtual int Initialize();
	virtual int Update(long time);
	virtual int Draw(long time);
	virtual int LoadContent();

private:
	struct meshVertex *vtx;
	long *ind;
	int createVtxDescription(void);
	int createGraphicsBuffers(void);

	float dx;
	float dz;

	int numRows;
	int numCols;

	static IDirect3DVertexDeclaration9* mDecl;
};