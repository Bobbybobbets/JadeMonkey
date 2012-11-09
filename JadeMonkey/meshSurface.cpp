

//=============================================================================
// meshSurface.cpp 
//
//Author: Doron Nussbaum (C) 2011 All Rights Reserved.
//-----------------------------------------------------
//
// Purpose: 
//--------------
// a. demonstrates the creation of a surface and of vertex and index buffers
// b. demonstartes how to rpesent a surface 
//
//
// Description:
//--------------
//
//
//
// License
//--------------
//
// Code can be used for instructional and educational purposes and for assignments in the gaming courses at 
// the School of Compuer Science at Carleton University.
// Usage of code for other purposes is not allowed without a given permission by the author.
//
//
// Disclaimer
//--------------
//
// The code is provided as is without any warranty

//=============================================================================



#include "StdAfx.h"
#include "meshSurface.h"
#include "jade_util.h"





IDirect3DVertexDeclaration9* meshSurface::mDecl = NULL;

/******************************************************************/
/*
Purpose: meshSurface destructor


Descripton: releases all allocated memory and com objects

Return:

*/

meshSurface::~meshSurface(void)
{
	// releae the com objects
	COM_RELEASE(this->mDecl);
	COM_RELEASE(this->mVtxBuf);
	COM_RELEASE(this->mIndBuf);

	// free the memory
	FREE_MEMORY_MALLOC(vtx);
	FREE_MEMORY_MALLOC(ind);
	
}

/******************************************************************/
/*
Purpose: meshSurface constructor


Descripton: creates a surface with numRows x NumCols vertices and (numRows-1) x (NumCols-1)
quads.  Each quad size is dx x dz.  

Note that the y axis represents the height and the mesh spans the x-z axis.

Return:

*/
meshSurface::meshSurface(int numRows, int numCols, float dx, float dz, Game *game) : GameEntity(game){
	this->ind=0; 
	this->numVtx=0; 
	this->numQuads=0;
	this->numTriangles=0;
	this->dz = dz;
	this->dx = dx;
	this->vtx=NULL;
	this->numRows=numRows;
	this->numCols=numCols;
	createVtxDescription();
	Initialize();
}

/******************************************************************/
/*
Purpose: generates the surface - the vertices and the quads


Descripton: creates a surface with numRows x NumCols vertices and (numRows-1) x (NumCols-1)
quads.  Each quad size is dx x dz.  

It allocates the required memory and store the vertices and quads with the object.  It also 
creats the required buffer on the graphics card.

The generated mesh is index based.

Note that the y axis represents the height and the mesh spans the x-z axis.

Return:
0 if success
*/


int meshSurface::Initialize()
{	
	int rc = 0;
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

	// allocate memory
	vtx = (struct meshVertex *) malloc(sizeof(struct meshVertex) * numVtx);
	if (vtx == NULL) {
		// error
		rc = 1;
		goto err;
	}

	ind = (long *) malloc(sizeof(long) * numTriangles * 3);
	if (ind == NULL) {
		// error
		rc = 1;
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
	createGraphicsBuffers();

	return(rc);
err:
	// clean up
	FREE_MEMORY_MALLOC(vtx);
	FREE_MEMORY_MALLOC(ind);

	return(rc);
}


/******************************************************************/
/*
Purpose: creates the required index and vertex buffers on the graphics card


Descripton: 

Return:
0 if success

*/


int meshSurface::createGraphicsBuffers(void)
{
	int rc = 0;
	struct meshVertex *v = NULL;
	long *ind = NULL;


#ifdef NUSS_SHADERS
	rc =  md3dDev->CreateVertexBuffer(this->numVtx*sizeof(struct meshVertex),D3DUSAGE_WRITEONLY,
										NULL,D3DPOOL_MANAGED,&this->mVtxBuf, NULL);
#else 
	rc =  md3dDev->CreateVertexBuffer(this->numVtx*sizeof(struct meshVertex),D3DUSAGE_WRITEONLY,
										MESH_VERTEX_FVF,D3DPOOL_MANAGED,&this->mVtxBuf, NULL);
#endif


	// lock the buffer and copy the vertices (locking the entire array
	rc = mVtxBuf->Lock(0, 0, (void **) &v, 0);
	if (rc != D3D_OK) {
		goto err;
	}

	memcpy(v, this->vtx,numVtx*sizeof(struct meshVertex));

	rc = mVtxBuf->Unlock();


	rc =  md3dDev->CreateIndexBuffer(this->numTriangles*3*sizeof(long),D3DUSAGE_WRITEONLY,
										D3DFMT_INDEX32,D3DPOOL_MANAGED,&this->mIndBuf, NULL);


	// lock the buffer and copy the vertices (locking the entire array
	rc = mIndBuf->Lock(0, 0, (void **) &ind, 0);
	if (rc != D3D_OK) {
		goto err;
	}

	memcpy(ind, this->ind,numTriangles*3*sizeof(long));

	rc = mIndBuf->Unlock();

	if (rc != D3D_OK) {
		goto err;
	}



	return 0;

err:
	return(rc);
}

/******************************************************************/
/*
Purpose: creates the vertex description interface


Descripton: 

Return:
0 if success
*/



int meshSurface::createVtxDescription(void)
{
	int rc = 0;
	// create the vertex decalation
	if (this->mDecl == NULL) {
		struct meshVertex v;
		D3DVERTEXELEMENT9 decl[] = 
		{{0,0,D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		 {0,0,D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()};
		decl[0].Offset = (char *) &v.pos - (char *) &v;
		decl[1].Offset = (char *) &v.color - (char *) &v;
		rc = md3dDev->CreateVertexDeclaration(decl, &mDecl);
	}


	return 0;
}

/******************************************************************/
/*
Purpose: change the position of the sufce.


Descripton: set the position of hte surfce.  The srufce should be 
translated so the the vertex at (0,?,0) is moved to 
Return:

*/


//int meshSurface::setCentrePosition(D3DXVECTOR3 centrePos)
//{
	// to be udpated 
//	this->mPosition = centrePos;
//	return 0;
//}


/******************************************************************/
/*
Purpose: renders the surface


Descripton: 


Return:

*/


int meshSurface::Draw(long time)
{

	int rc;
    static int angle = 0;

	static float step = 1;
	float rad = 0;

	static int i=0, j=0, k=0;

	D3DXMATRIX worldMat, viewMat, matTransform, matProjection, matScale, matTranslate,  matRotation;


	D3DXMatrixScaling(&matScale,_scale.x, _scale.y, _scale.z);
	worldMat = matScale;

	D3DXMatrixTranslation(&matTranslate, _position.x, _position.y, _position.z);
	worldMat *= matTranslate;


	//D3DXMatrixIdentity(&worldMat);
	md3dDev->SetTransform(D3DTS_WORLD, &worldMat);

	// set the source
	rc = md3dDev->SetStreamSource( 0, mVtxBuf, 0, sizeof(meshVertex) );
#ifdef NUSS_SHADERS
	rc = md3dDev->SetVertexDeclaration(mDecl);
#else
	rc = md3dDev->SetFVF(MESH_VERTEX_FVF);
#endif


	// set the index buffer
	md3dDev->SetIndices(mIndBuf);

	// do  not use texture
	md3dDev->SetTexture(0,NULL);

	//md3dDev->SetRenderState(D3DRS_COLORVERTEX, FALSE);
	md3dDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//md3dDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	md3dDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, this->numVtx, 0, this->numTriangles);

   
	return 0;
}



/******************************************************************/
/*
Purpose: sets the surface scaling factor


Descripton: set the position of hte surfce.  The srufce should be 
translated so the the vertex at (0,?,0) is moved to 
Return:

*/


int meshSurface::Update(long time) {
	return 0;
}

int meshSurface::LoadContent(void) {
	return 0;
}



void meshSurface::setScale(float x, float y, float z)
{
	this->_scale.x = x;
	this->_scale.y = y;
	this->_scale.z = z;
}
