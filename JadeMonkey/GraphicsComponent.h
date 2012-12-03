#pragma once

#include "BEntityComponent.h"
#include "GameEntity.h"

#define NUSS_SHADERS 1

struct MeshVertex {
	D3DXVECTOR3 pos;
    DWORD color;        // The vertex color
};

struct MeshDefinition
{
	struct MeshVertex* Vertices;
	unsigned int Size;
};

#ifndef NUSS_SHADERS
#define MESH_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#endif

class GraphicsComponent : public BEntityComponent
{
public:
	GraphicsComponent(Game* game, GameEntity* entity);
	virtual void Initialize(void) = 0;
	virtual void Update(GameEntity* entity, long time);
	virtual string GetName(void);
	struct MeshDefinition GetMesh(void);

	virtual int getNumRows() override;
	int getNumCols() override ;
	float getDx() override ;
	float getDy() override ;
	float getDz() override;

protected:
	virtual void createGraphicsBuffers(void);
	virtual void createVtxDescription(void);

	struct MeshVertex *vtx;
	long *ind;
	IDirect3DIndexBuffer9 *mIndBuf;
	IDirect3DVertexBuffer9 *mVtxBuf;

	float dx;
	float dy;
	float dz;

	int numRows;
	int numCols;
	int numVtx;
	int numQuads;
	int numTriangles;
	int numIndices;
	int fill;

	static IDirect3DVertexDeclaration9* mDecl;

};