#include "GraphicsComponent.h"

IDirect3DVertexDeclaration9* GraphicsComponent::mDecl = NULL;

GraphicsComponent::GraphicsComponent(Game* game, GameEntity* entity): BDrawableEntityComponent(game, entity)
{
}

GraphicsComponent::~GraphicsComponent()
{
}

void GraphicsComponent::Initialize(void)
{
	this->loadMesh();
}

MeshDefinition GraphicsComponent::GetMesh(void)
{
	MeshDefinition def;
	def.Vertices = this->vtx;
	def.Size = this->numVtx;

	return def;
}

void GraphicsComponent::Update(GameEntity* entity, long time)
{
}

void GraphicsComponent::setupRender(void)
{
	D3DXVECTOR3 _position = this->_entity->getPosition();
	D3DXVECTOR3 _scale = this->_entity->getScale();
	D3DXVECTOR3 yaxis = D3DXVECTOR3(0.0, 1.0, 0.0);
	D3DXVECTOR3 xaxis = D3DXVECTOR3(1.0,0.0,0.0);

    static int angle = 0;

	static float step = 1;
	float rad = 0;

	static int i=0, j=0, k=0;

	D3DXMATRIX worldMat, viewMat, matTransform, matProjection, matScale, matTranslate,  matRotation;

	//Declare the rotation axis based on the x and y axis 


	D3DXMatrixScaling(&matScale,_scale.x, _scale.y, _scale.z);
	worldMat = matScale;

	if( this->_entity->getRotation().y > 0)
		D3DXMatrixRotationAxis(&matRotation, &yaxis, -D3DXToRadian(this->_entity->getRotation().y));
	else 
		D3DXMatrixRotationAxis(&matRotation, &yaxis, D3DXToRadian(this->_entity->getRotation().y));

	if( this->_entity->getRotation().x != 0)
	{
		if( this->_entity->getRotation().x > 0)
			D3DXMatrixRotationAxis(&matRotation, &xaxis, D3DXToRadian(this->_entity->getRotation().x));
		else
			D3DXMatrixRotationAxis(&matRotation, &xaxis, -D3DXToRadian(this->_entity->getRotation().x));
	}
	worldMat *= matRotation;
	D3DXMatrixTranslation(&matTranslate, _position.x, _position.y, _position.z);
	worldMat *= matTranslate;

	_game->getGraphicsDevice()->SetTransform(D3DTS_WORLD, &worldMat);

	// set the source
	_game->getGraphicsDevice()->SetStreamSource( 0, mVtxBuf, 0, sizeof(MeshVertex) );
/*
#ifdef NUSS_SHADERS
	_game->getGraphicsDevice()->SetVertexDeclaration(mDecl);
#else*/
	_game->getGraphicsDevice()->SetFVF(MESH_VERTEX_FVF);
//#endif


	// set the index buffer
	_game->getGraphicsDevice()->SetIndices(mIndBuf);

	// do  not use texture
	_game->getGraphicsDevice()->SetTexture(0,NULL);
	_game->getGraphicsDevice()->SetRenderState(D3DRS_FILLMODE,  D3DFILL_SOLID);//D3DFILLMODE(fill));// ); SOLID = 3
}

void GraphicsComponent::Draw(long time)
{
	
	this->setupRender();
	_game->getGraphicsDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->numVtx, 0, this->numTriangles);
}

void GraphicsComponent::createGraphicsBuffers(void)
{
	struct MeshVertex *v = NULL;
	long *ind = NULL;

	_game->getGraphicsDevice()->CreateVertexBuffer(
		this->numVtx*sizeof(struct MeshVertex),
		D3DUSAGE_WRITEONLY,
		MESH_VERTEX_FVF,
		D3DPOOL_MANAGED,
		&this->mVtxBuf, 
		NULL);


	// lock the buffer and copy the vertices (locking the entire array
	mVtxBuf->Lock(0, 0, (void **) &v, 0);


	memcpy(v, this->vtx,numVtx*sizeof(struct MeshVertex));

	mVtxBuf->Unlock();


	_game->getGraphicsDevice()->CreateIndexBuffer(this->numTriangles*3*sizeof(long),D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX32,D3DPOOL_MANAGED,&this->mIndBuf, NULL);


	// lock the buffer and copy the vertices (locking the entire array
	mIndBuf->Lock(0, 0, (void **) &ind, 0);
	/*if (rc != D3D_OK) {
		goto err;
	}*/

	memcpy(ind, this->ind,numTriangles*3*sizeof(long));

	mIndBuf->Unlock();
}

void GraphicsComponent::createVtxDescription(void)
{
	// create the vertex decalation
	if (this->mDecl == NULL) {
		struct MeshVertex v;
		D3DVERTEXELEMENT9 decl[] = 
		{{0,0,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		 {0,0,D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()};
		decl[0].Offset = (char *) &v.pos - (char *) &v;
		decl[1].Offset = (char *) &v.color - (char *) &v;
		_game->getGraphicsDevice()->CreateVertexDeclaration(decl, &mDecl);
	}
}

int GraphicsComponent::getNumRows()
{
	return numRows;
}
int GraphicsComponent::getNumCols()
{
	return numCols;
}
float GraphicsComponent::getDx()
{
	return dx;
}
float GraphicsComponent::getDy()
{
	return dy;
}
float GraphicsComponent::getDz()
{
	return dz;
}
string GraphicsComponent::GetName()
{
	return "Graphics component";
}