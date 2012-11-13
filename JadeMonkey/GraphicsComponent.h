#include "BEntityComponent.h"
#include "GameEntity.h"

#define NUSS_SHADERS 1

struct meshVertex {
	D3DXVECTOR3 pos;
    DWORD color;        // The vertex color

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
	virtual string GetName(void) = 0;

protected:
	virtual void createGraphicsBuffers(void);
	virtual void createVtxDescription(void);

	struct meshVertex *vtx;
	long *ind;
	IDirect3DIndexBuffer9 *mIndBuf;
	IDirect3DVertexBuffer9 *mVtxBuf;

	float dx;
	float dz;

	int numRows;
	int numCols;
	int numVtx;
	int numQuads;
	int numTriangles;

	static IDirect3DVertexDeclaration9* mDecl;
};