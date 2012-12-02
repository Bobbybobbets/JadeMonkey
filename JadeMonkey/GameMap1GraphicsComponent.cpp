#include "GameMap1GraphicsComponent.h"
#include "jade_util.h"

GameMap1GraphicsComponent::GameMap1GraphicsComponent(int numRows, int numCols, Game* game, GameEntity* entity)
	: GraphicsComponent(game, entity)
{
	this->ind=0; 
	this->numVtx=0; 
	this->numQuads=0;
	this->numTriangles=0;
	this->dz = 20;
	this->dx = 20;
	this->vtx=NULL;
	this->numRows=numRows;
	this->numCols=numCols;
	createVtxDescription();
	this->_entity->setScale(D3DXVECTOR3(1.0, 4.0, 1.0));
}

void GameMap1GraphicsComponent::Initialize(void)
{
	int i,j,k;
	D3DXVECTOR3 rowPos(0.0,0.0,0.0);
	D3DXVECTOR3 colPos(0.0,0.0,0.0);
	D3DCOLOR initialColor = D3DCOLOR_XRGB(150, 100, 50);
	float rangeMax = 10;
	float rangeMin = 0;

	numVtx = numRows*numCols;
	this->numRows = numRows;
	this->numCols = numCols;
	this->dx = dx;
	this->dz = dz;

	numQuads = (numRows-1) * (numCols-1);
	numTriangles = numQuads * 2;
	numIndices = numTriangles * 3;

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


	k = 0;
	for(i = 0; i < numRows; i++) {
		// assign the pos vector for all comumns in a row
		colPos = rowPos;
		for(j = 0; j < numCols; j++) {
			// Negate the depth coordinate to put in quadrant four.  
			// Then offset to center about coordinate system.
			vtx[k].pos =  colPos;
			//vtx[k].pos.y = (long)((double)rand()/(RAND_MAX+1) * (rangeMax - rangeMin)
			//	+ rangeMin);
			vtx[k].pos.y = 0;
			vtx[k].color = initialColor;
			colPos.x += dx;
			k++;
		}
		rowPos.z += dz;
	}

	// fill the index buffer

	k = 0;
	for(i = 0; i < numRows-1; i++) {
		for(j = 0; j < numCols-1; j++)
		{
			// fill indices for the quad
			ind[k++] = i * numCols + j;
			ind[k++] = (i+1) * numCols + j + 1;
			ind[k++] = i * numCols + j + 1;
			
			ind[k++] = i * numCols + j;
			ind[k++] = (i+1) * numCols + j;
			ind[k++] = (i+1) * numCols + j + 1;

		}
	}

	// allocate memory in the graphics card memory for the vertices and the index buffer
	this->createGraphicsBuffers();
err:
	// clean up
	FREE_MEMORY_MALLOC(vtx);
	FREE_MEMORY_MALLOC(ind);
}

void GameMap1GraphicsComponent::Update(GameEntity* entity, long time)
{
	GraphicsComponent::Update(this->_entity, time);
}

string GameMap1GraphicsComponent::GetName(void)
{
	return "GameMap1GraphicsComponent";
}