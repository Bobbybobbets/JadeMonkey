#include "KeyGraphicsComponent.h"
#include "jade_util.h"
#include "RessourceManager.h"


KeyGraphicsComponent::KeyGraphicsComponent(int dx, int dy, PlayerComponent *player, KeyPartComponent *keyPart, Game* game, GameEntity* entity): TexturedGraphicsComponent(game, entity)
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
	this->loadTexture();
}

void KeyGraphicsComponent::Initialize(void)
{
	this->loadMesh();

	

}

void KeyGraphicsComponent::Update(GameEntity* entity, long time)
{
}

void KeyGraphicsComponent::setupRender()
{
	 D3DXVECTOR3 _position = this->_entity->getPosition();
	 D3DXVECTOR3 _scale = this->_entity->getScale();
	 D3DXVECTOR3 yaxis = D3DXVECTOR3(0.0, 1.0, 0.0);
	 float rad = 0;

	 D3DXMATRIX worldMat, viewMat, matTransform, matProjection, matScale, matTranslate,  matRotation, billboardMat;


	//  If they key has already been retrieved 
	if( _keyPart->getRetrieved())
		return;

	 D3DXVECTOR3 toLookAt = _player->getEntity()->getPosition() - this->_entity->getPosition(); 
	 D3DXMatrixScaling(&matScale,_scale.x, _scale.y, _scale.z);
	 worldMat = matScale;

	 D3DXMatrixIdentity(&viewMat);
	 D3DXMatrixIdentity(&billboardMat);

	 this->_game->getGraphicsDevice()->GetTransform(D3DTS_VIEW, &viewMat);

	 D3DXMatrixInverse(&billboardMat, NULL, &viewMat);
	 billboardMat._41 = 0.0f;
	 billboardMat._42 = 0.0f;
	 billboardMat._43 = 0.0f;

	 worldMat *= billboardMat;

	 D3DXMatrixTranslation(&matTranslate, _position.x, _position.y, _position.z);
	 worldMat *= matTranslate;

	 _game->getGraphicsDevice()->SetTransform(D3DTS_WORLD, &worldMat);

	 // set the source
	// set the source
	_game->getGraphicsDevice()->SetStreamSource( 0, mVtxBuf, 0, sizeof(MeshVertex) );

	/*#ifdef NUSS_SHADERS
	 _game->getGraphicsDevice()->SetVertexDeclaration(mDecl);
	#else*/
	_game->getGraphicsDevice()->SetFVF(MESH_VERTEX_FVF);
	//#endif


	 // set the index buffer
	 _game->getGraphicsDevice()->SetIndices(mIndBuf);

	 _game->getGraphicsDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	_game->getGraphicsDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->numVtx, 0, this->numTriangles);

	_game->getGraphicsDevice()->SetTexture(0, this->_texture);
	_game->getGraphicsDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	_game->getGraphicsDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_game->getGraphicsDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	_game->getGraphicsDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	_game->getGraphicsDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	 // do  not use texture
//	_game->getGraphicsDevice()->SetTexture(0,NULL);
}

int KeyGraphicsComponent::getHeight()
{
	return numRows * dy;
}

string KeyGraphicsComponent::GetName(void)
{
	return "KeyGraphicsComponent";
}

void KeyGraphicsComponent::loadMesh(void)
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
	vtx[0].tex1= D3DXVECTOR2(0,1);
	vtx[1].pos = D3DXVECTOR3(0,20,0);
	vtx[1].tex1 = D3DXVECTOR2(0,0);
	vtx[2].pos = D3DXVECTOR3(20,20,0);
	vtx[2].tex1 = D3DXVECTOR2(1,0);
	vtx[3].pos = D3DXVECTOR3(20,0,0);
	vtx[3].tex1 = D3DXVECTOR2(1,1);

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

void KeyGraphicsComponent::loadTexture()
{
	this->_texture = RessourceManager::GetTexture(this->_game->getGraphicsDevice(), "Textures/Bananastub2.jpg");
}