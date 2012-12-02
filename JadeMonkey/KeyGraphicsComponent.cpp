#include "KeyGraphicsComponent.h"
#include "jade_util.h"


KeyGraphicsComponent::KeyGraphicsComponent(int dx, int dy, PlayerComponent *player, KeyPartComponent *keyPart, Game* game, GameEntity* entity): GraphicsComponent(game, entity)
{
	this->_player = player;
	this->_keyPart = keyPart;
	this->ind=0; 
	this->numVtx=0; 
	this->numQuads=0;
	this->numTriangles=0;
	this->dy = dy;
	this->dx = dx;
	this->vtx=NULL;
	this->numRows=1;
	this->numCols=1;
	createVtxDescription();
	this->_entity->setScale(D3DXVECTOR3(1.0, 1.0, 1.0));
}

void KeyGraphicsComponent::Initialize(void)
{
	int i,j,k;
	D3DXVECTOR3 rowPos(0.0,0.0,0.0);
	D3DXVECTOR3 colPos(0.0,0.0,0.0);
	D3DCOLOR initialColor = D3DCOLOR_XRGB(150, 100, 50);
	float rangeMax = 10;
	float rangeMin = 0;

	numVtx = 4;
	numQuads = 1;
	numTriangles = numQuads * 2;

	// allocate memory
	vtx = (struct MeshVertex *) malloc(sizeof(struct MeshVertex) * numVtx);
	if (vtx == NULL) {
		// error
		goto err;
	}

	ind = (long *) malloc(sizeof(long) * numTriangles * 3);
	if (ind == NULL) {
		// error
		goto err;
	}

	// Fill the vertex buffer with positions

	vtx[0].pos = D3DXVECTOR3(0,0,0);
	vtx[1].pos = D3DXVECTOR3(0,20,0);
	vtx[2].pos = D3DXVECTOR3(20,20,0);
	vtx[3].pos = D3DXVECTOR3(20,0,0);

	ind[0] = 0;
	ind[1] = 1;
	ind[2] = 2;
	ind[3] = 0;
	ind[4] = 2;
	ind[5] = 3;

	// allocate memory in the graphics card memory for the vertices and the index buffer*/
	this->createGraphicsBuffers();
err:
	// clean up
	FREE_MEMORY_MALLOC(vtx);
	FREE_MEMORY_MALLOC(ind);
}

void KeyGraphicsComponent::Update(GameEntity* entity, long time)
{
	D3DXVECTOR3 _position = this->_entity->getPosition();
	D3DXVECTOR3 _scale = this->_entity->getScale();
	D3DXVECTOR3 yaxis = D3DXVECTOR3(0.0, 1.0, 0.0);
	float rad = 0;

	D3DXMATRIX worldMat, viewMat, matTransform, matProjection, matScale, matTranslate,  matRotation;


	// If they key has already been retrieved 
//	if( _keyPart->getRetrieved())
//		return;

	D3DXVECTOR3 toLookAt = _player->getEntity()->getPosition() - this->_entity->getPosition();
	D3DXVECTOR3 upVector;
	//D3DXVec3Cross(&upVector, &toLookAt, &target);
	//Declare the rotation axis based on the x and y axis 
	//D3DXMatrixLookAtLH(&viewMat, &this->_entity->getPosition(), &this->_player->getEntity()->getPosition(), &D3DXVECTOR3(0,1,0));



	D3DXMatrixScaling(&matScale,_scale.x, _scale.y, _scale.z);
	worldMat = matScale;



	D3DXMatrixTranslation(&matTranslate, _position.x, _position.y, _position.z);
	worldMat *= matTranslate;

	_game->getGraphicsDevice()->SetTransform(D3DTS_WORLD, &worldMat);

	// set the source
	_game->getGraphicsDevice()->SetStreamSource( 0, mVtxBuf, 0, sizeof(MeshVertex) );

#ifdef NUSS_SHADERS
	_game->getGraphicsDevice()->SetVertexDeclaration(mDecl);
#else
	rc = _game->getGraphicsDevice()->SetFVF(MESH_VERTEX_FVF);
#endif


	// set the index buffer
	_game->getGraphicsDevice()->SetIndices(mIndBuf);

	// do  not use texture
	_game->getGraphicsDevice()->SetTexture(0,NULL);
	_game->getGraphicsDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	_game->getGraphicsDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->numVtx, 0, this->numTriangles);
}

int KeyGraphicsComponent::getHeight()
{
	return numRows * dy;
}

string KeyGraphicsComponent::GetName(void)
{
	return "KeyGraphicsComponent";
}