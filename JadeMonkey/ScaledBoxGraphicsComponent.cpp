#include "ScaledBoxGraphicsComponent.h"
#include "jade_util.h"

ScaledBoxGraphicsComponent::ScaledBoxGraphicsComponent(Game* game, GameEntity* entity, D3DCOLOR color)
	: GraphicsComponent(game, entity)
{
	this->ind=0; 
	this->numVtx=0; 
	this->numQuads=0;
	this->numTriangles=0;
	this->vtx = NULL;
	this->_color = color;
	createVtxDescription();
}

void ScaledBoxGraphicsComponent::Initialize(void)
{
	/*D3DXVECTOR3 entitySize = this->_entity->getSize();
	this->numVtx = 8;
	this->numQuads = 6;
	this->numTriangles = this->numQuads*2;
	this->numIndices = this->numTriangles*3;
	this->vtx = (MeshVertex*)malloc(this->numVtx * sizeof(MeshVertex));
	this->ind = (long*)malloc(this->numIndices * sizeof(long));

	//create vertex data
	this->vtx[0] = MeshVertex(D3DXVECTOR3(-entitySize.x/2, entitySize.y/2, -entitySize.z/2), this->_color);
	this->vtx[1] = MeshVertex(D3DXVECTOR3(entitySize.x/2, entitySize.y/2, -entitySize.z/2), this->_color);
	this->vtx[2] = MeshVertex(D3DXVECTOR3(-entitySize.x/2, -entitySize.y/2, -entitySize.z/2), this->_color);
	this->vtx[3] = MeshVertex(D3DXVECTOR3(entitySize.x/2, -entitySize.y/2, -entitySize.z/2), this->_color);
	this->vtx[4] = MeshVertex(D3DXVECTOR3(-entitySize.x/2, entitySize.y/2, entitySize.z/2), this->_color);
	this->vtx[5] = MeshVertex(D3DXVECTOR3(entitySize.x/2, entitySize.y/2, entitySize.z/2), this->_color);
	this->vtx[6] = MeshVertex(D3DXVECTOR3(-entitySize.x/2, -entitySize.y/2, entitySize.z/2), this->_color);
	this->vtx[7] = MeshVertex(D3DXVECTOR3(entitySize.x/2, -entitySize.y/2, entitySize.z/2), this->_color);

	//define indices
	long stackArray[] = {
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	//std::copy(this->ind, this->ind + this->numIndices, &stackArray[0]);
	memcpy((void*)this->ind, (void*)&stackArray[0], 36*sizeof(long));
	this->createGraphicsBuffers();

	// clean up
	FREE_MEMORY_MALLOC(vtx);
	FREE_MEMORY_MALLOC(ind);*/

	D3DXVECTOR3 entitySize = this->_entity->getSize();

	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[] =
	{
		{ -entitySize.x/2, entitySize.y/2, -entitySize.z/2, this->_color, },
		{ entitySize.x/2, entitySize.y/2, -entitySize.z/2, this->_color, },
		{ -entitySize.x/2, -entitySize.y/2, -entitySize.z/2, this->_color, },
		{ entitySize.x/2, -entitySize.y/2, -entitySize.z/2, this->_color, },
		{ -entitySize.x/2, entitySize.y/2, entitySize.z/2, this->_color, },
		{ entitySize.x/2, entitySize.y/2, entitySize.z/2, this->_color, },
		{ -entitySize.x/2, -entitySize.y/2, entitySize.z/2, this->_color, },
		{ entitySize.x/2, -entitySize.y/2, entitySize.z/2, this->_color, },
	};

	// create a vertex buffer interface called v_buffer
	IDirect3DDevice9* d3ddev = this->_game->getGraphicsDevice();
	d3ddev->CreateVertexBuffer(
		8*sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	VOID* pVoid;    // a void pointer

	// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	// create the indices using an int array
	short indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	// create an index buffer interface called i_buffer
	d3ddev->CreateIndexBuffer(36*sizeof(short),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&i_buffer,
		NULL);

	// lock i_buffer and load the indices into it
	i_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	i_buffer->Unlock();
}


void ScaledBoxGraphicsComponent::Update(GameEntity* entity, long time)
{
	D3DXVECTOR3 _position = this->_entity->getPosition();
	D3DXVECTOR3 _scale = this->_entity->getScale();
	D3DXVECTOR3 yaxis = D3DXVECTOR3(0, 1, 0);

	static int angle = 0;

	static float step = 1;
	float rad = 0;

	static int i=0, j=0, k=0;

	D3DXMATRIX worldMat, matScale, matTranslate,  matRotation;

	//Declare the rotation axis based on the x and y axis 

	
	D3DXMatrixScaling(&matScale,_scale.x, _scale.y, _scale.z);
	worldMat = matScale;

	if( this->_entity->getRotation().y > 0)
		D3DXMatrixRotationAxis(&matRotation, &yaxis, -D3DXToRadian(this->_entity->getRotation().y));
	else 
		D3DXMatrixRotationAxis(&matRotation, &yaxis, D3DXToRadian(this->_entity->getRotation().y));

	worldMat *= matRotation;
	D3DXMatrixTranslation(&matTranslate, _position.x, _position.y, _position.z);
	worldMat *= matTranslate;

	_game->getGraphicsDevice()->SetTransform(D3DTS_WORLD, &worldMat);

	// select the vertex and index buffers to use
	IDirect3DDevice9* d3ddev = this->_game->getGraphicsDevice();
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(i_buffer);

	d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	// draw the cube
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

string ScaledBoxGraphicsComponent::GetName()
{
	return "ScaledBoxComponent";
}