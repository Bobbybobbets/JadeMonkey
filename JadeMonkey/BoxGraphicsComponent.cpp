#include "BoxGraphicsComponent.h"
#include <algorithm>

BoxGraphicsComponent::BoxGraphicsComponent(Game* game, GameEntity* entity, D3DCOLOR color)
	: GraphicsComponent(game, entity)
{
	this->_color = color;
}

void BoxGraphicsComponent::Initialize(void)
{
	D3DXVECTOR3 entitySize = this->_entity->getSize();
	this->vtx = (MeshVertex*)malloc(8 * sizeof(MeshVertex));
	this->ind = (long*)malloc(24 * sizeof(long));
	this->numQuads = 6;
	this->numTriangles = this->numQuads*2;
	this->numIndices = this->numTriangles*3;


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
	int stackArray[] = {
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

	std::copy(this->ind, this->ind + this->numIndices, &stackArray[0]);
}

void BoxGraphicsComponent::Update(GameEntity* entity, long time)
{
	GraphicsComponent::Update(this->_entity, time);
}

string BoxGraphicsComponent::GetName(void)
{
	return "GraphicsComponent";
}