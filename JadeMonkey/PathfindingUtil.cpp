#include "PathfindingUtil.h"

AStarPathfindingGraph* PathfindingUtil::CreateAStarGraphFromFloors(
	unsigned int rows,
	unsigned int cols,
	float dx,
	float dz,
	D3DXVECTOR3 position)
{
	D3DXVECTOR3 pos = position*20;
	unsigned int size = rows * cols;
	AStarNode* nodes = new AStarNode[size]();
	int k = 0;
	AStarPathfindingGraph* graph;
	int pSize = sizeof(AStarNode);
	int nSize = sizeof nodes;
	int arraySize = sizeof(nodes) / sizeof(nodes[0]);

	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
		{
			nodes[k] = AStarNode(pos + D3DXVECTOR3(j*dx, 0, i*dz));
			++k;
		}
	}

	k = 0;
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
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
				nodes[k].AddNeighbour(&nodes[top], Top);

				if(allowLeft)
					nodes[k].AddNeighbour(&nodes[topLeft], TopLeft);
				if(allowRight)
					nodes[k].AddNeighbour(&nodes[topRight], TopRight);
			}
			if(allowBot)	
			{
				nodes[k].AddNeighbour(&nodes[bot], Down);
				if(allowRight)
					nodes[k].AddNeighbour(&nodes[botRight], DownRight);
				if(allowLeft)
					nodes[k].AddNeighbour(&nodes[botLeft], DownLeft);
			}
			if(allowRight)
			{
				nodes[k].AddNeighbour(&nodes[right], Right);
			}
			if(allowLeft)
			{
				nodes[k].AddNeighbour(&nodes[left], Left);
			}

			k++;
		}
	}

	graph = new AStarPathfindingGraph(pos, nodes, size, rows, cols, dx, dz);

	return graph;
}