#pragma once

#include "BDrawableEntityComponent.h"
#include "GameEntity.h"

struct MeshVertex {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 normal;
	D3DXVECTOR2 tex1;
};

struct MeshDefinition
{
	struct MeshVertex* Vertices;
	unsigned int Size;
};

#define MESH_VERTEX_FVF (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)


class GraphicsComponent : public BDrawableEntityComponent
{
public:
	GraphicsComponent(Game* game, GameEntity* entity);
	~GraphicsComponent();
	virtual void Initialize(void);
	virtual void Update(GameEntity* entity, long time);
	virtual void Draw(long time);
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
	virtual void loadMesh(void) = 0;
	virtual void setupRender(void);

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