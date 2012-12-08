#include "PathfindingUtil.h"
#include <vector>
#include "VectorUtil.h"

AStarPathfindingGraph* PathfindingUtil::CreateAStarGraphFromFloors(
	unsigned int rows,
	unsigned int cols,
	float dx,
	float dz,
	D3DXVECTOR3 position,
	vector<D3DRECT> collisionRects)
{
	D3DXVECTOR3 pos = position*20;
	unsigned int size = rows * cols;
	AStarNode** nodes = new AStarNode*[size]();
	vector<AStarNode*>* retNodes = new vector<AStarNode*>();
	int k = 0;
	int f = 0;
	AStarPathfindingGraph* graph;
	int pSize = sizeof(AStarNode);
	int nSize = sizeof nodes;
	int arraySize = sizeof(nodes) / sizeof(nodes[0]);

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			D3DXVECTOR3 nodePos = pos + D3DXVECTOR3(j*dx, 10, i*dz);
			bool validZone = true;
			
			for(vector<D3DRECT>::iterator it = collisionRects.begin();
				it < collisionRects.end();
				it++)
			{
				if(VectorUtil::PointInRect2f(D3DXVECTOR2(nodePos.x, nodePos.y), (*it)))
				{
					validZone = false;
				}
			}
			
			if(validZone)
			{
				nodes[k] = new AStarNode(nodePos);
			}
			else
			{
				nodes[k] = 0;
			}

			++k;
		}
	}

	k = 0;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			if(nodes[k] != 0)
			{
				int topLeft = (i-1)*cols + (j-1);
				int top = (i-1)*cols + j;
				int topRight = (i-1)*cols + (j+1);
				int right = i*cols + (j+1);
				int botRight = (i+1)*cols + (j+1);
				int bot = (i+1)*cols + j;
				int botLeft = (i+1)*cols + (j-1);
				int left = i*cols + (j-1);

				bool allowTop = false;
				bool allowRight = false;
				bool allowBot = false;
				bool allowLeft = false;

				//can only do top if this is true
				if(i != 0)
				{
					allowTop = true;
				}
				if(i != rows - 1) //can only do down if this is true
				{
					allowBot = true;
				}
				if(j != 0)//can only go left if this is true
				{
					allowLeft = true;
				}
				if(j != cols - 1) //can only go right if this is true
				{
					allowRight = true;
				}

				if(allowTop)
				{
					if(nodes[top] != 0)
						nodes[k]->AddNeighbour(nodes[top], Top);

					if(allowLeft)
					{
						if(nodes[topLeft] != 0)
							nodes[k]->AddNeighbour(nodes[topLeft], TopLeft);
					}
					if(allowRight)
					{
						if(nodes[topRight] != 0)
							nodes[k]->AddNeighbour(nodes[topRight], TopRight);
					}
				}
				if(allowBot)	
				{
					if(nodes[bot] != 0)
						nodes[k]->AddNeighbour(nodes[bot], Down);

					if(allowRight)
					{
						if(nodes[botRight] != 0)
							nodes[k]->AddNeighbour(nodes[botRight], DownRight);
					}
					if(allowLeft)
					{
						if(nodes[botLeft] != 0)
							nodes[k]->AddNeighbour(nodes[botLeft], DownLeft);
					}
				}
				if(allowRight)
				{
					if(nodes[right] != 0)
						nodes[k]->AddNeighbour(nodes[right], Right);
				}
				if(allowLeft)
				{
					if(nodes[left] != 0)
						nodes[k]->AddNeighbour(nodes[left], Left);
				}

				retNodes->push_back(nodes[k]);
			}
			k++;
		}
	}



	graph = new AStarPathfindingGraph(pos, nodes, size, rows, cols, dx, dz);

	return graph;
}