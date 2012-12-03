#include "GameMap2GraphicsComponent.h"
#include "jade_util.h"

GameMap2GraphicsComponent::GameMap2GraphicsComponent(int numRows, int numCols, Game* game, GameEntity* entity, int color)
	: GraphicsComponent(game, entity)
{
	this->ind=0; 
	this->numVtx=0; 
	this->numQuads=0;
	this->numTriangles=0;
	this->dy = 20;
	this->dx = 20;
	this->vtx=NULL;
	this->numRows=numRows;
	this->numCols=numCols;
	createVtxDescription();
	this->_entity->setScale(D3DXVECTOR3(1.0, 1.0, 1.0));
	this->color = color;
	fill = 3;
}

void GameMap2GraphicsComponent::Initialize(void)
{
	int i,j,k;
	D3DXVECTOR3 rowPos(0.0,0.0,0.0);
	D3DXVECTOR3 colPos(0.0,0.0,0.0);

	D3DCOLOR initialColor;
	if(color == 1)
		initialColor = D3DCOLOR_XRGB(36, 156, 36);
	else if (color == 2)
		initialColor = D3DCOLOR_XRGB(172,181,172);
	else
		initialColor = D3DCOLOR_XRGB(225,232,86);

	float rangeMax = 10;
	float rangeMin = 0;

	numVtx = numRows*numCols;
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
			vtx[k].pos.z = 0;
			vtx[k].color = initialColor;
			colPos.x += dx;
			k++;
		}
		rowPos.y += dy;
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

void GameMap2GraphicsComponent::Update(GameEntity* entity, long time)
{
	GraphicsComponent::Update(this->_entity, time);
}

int GameMap2GraphicsComponent::getHeight()
{
	return numRows * dy;
}

string GameMap2GraphicsComponent::GetName(void)
{
	return "GameMap1GraphicsComponent";
}