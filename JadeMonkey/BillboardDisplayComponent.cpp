#include "BillboardDisplayComponent.h"

BillboardDisplayComponent::BillboardDisplayComponent(Game* game, GameEntity* entity, GameEntity* player)
	: TexturedGraphicsComponent(game, entity)
{
	this->_player = player;
}

void BillboardDisplayComponent::setupRender(void)
{
	D3DXVECTOR3 _position = this->_entity->getPosition();
	D3DXVECTOR3 _scale = this->_entity->getScale();
	D3DXVECTOR3 yaxis = D3DXVECTOR3(0.0, 1.0, 0.0);
	float rad = 0;

	D3DXMATRIX worldMat, viewMat, matTransform, matProjection, matScale, matTranslate,  matRotation, billboardMat;

	D3DXVECTOR3 toLookAt = _player->getPosition() - this->_entity->getPosition(); 

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
	//_game->getGraphicsDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->numVtx, 0, this->numTriangles);

	_game->getGraphicsDevice()->SetTexture(0, this->_texture);
	//_game->getGraphicsDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	//_game->getGraphicsDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//_game->getGraphicsDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}

