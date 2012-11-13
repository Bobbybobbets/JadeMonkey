#include "CuboidCollisionComponent.h"

vector<CuboidPrism*> CuboidCollisionComponent::_globalBoundingBoxes = vector<CuboidPrism*>();

CuboidPrism::CuboidPrism(vector<D3DXVECTOR3> vertices)
{
	this->Vertices = vertices;
}

float CuboidPrism::MaxX(void)
{
	vector<D3DXVECTOR3>::iterator it;
	float max;

	for(it = this->Vertices.begin();
		it < this->Vertices.end();
		it++)
	{
		if(it == this->Vertices.begin())
		{
			max = (*it).x;
		}

		if(max < (*it).x)
		{
			max = (*it).x;
		}
	}
	return max;

}

float CuboidPrism::MaxY(void)
{
	vector<D3DXVECTOR3>::iterator it;
	float max;

	for(it = this->Vertices.begin();
		it < this->Vertices.end();
		it++)
	{
		if(it == this->Vertices.begin())
		{
			max = (*it).y;
		}

		if(max < (*it).y)
		{
			max = (*it).y;
		}
	}

	return max;
}

float CuboidPrism::MaxZ(void)
{
	vector<D3DXVECTOR3>::iterator it;
	float max;

	for(it = this->Vertices.begin();
		it < this->Vertices.end();
		it++)
	{
		if(it == this->Vertices.begin())
		{
			max = (*it).z;
		}

		if(max < (*it).z)
		{
			max = (*it).z;
		}
	}

	return max;
}

float CuboidPrism::MinX(void)
{
	vector<D3DXVECTOR3>::iterator it;
	float min;

	for(it = this->Vertices.begin();
		it < this->Vertices.end();
		it++)
	{
		if(it == this->Vertices.begin())
		{
			min = (*it).x;
		}

		if(min > (*it).x)
		{
			min = (*it).x;
		}
	}

	return min;
}

float CuboidPrism::MinY(void)
{
	vector<D3DXVECTOR3>::iterator it;
	float min;

	for(it = this->Vertices.begin();
		it < this->Vertices.end();
		it++)
	{
		if(it == this->Vertices.begin())
		{
			min = (*it).y;
		}

		if(min > (*it).y)
		{
			min = (*it).y;
		}
	}

	return min;
}

float CuboidPrism::MinZ(void)
{
	vector<D3DXVECTOR3>::iterator it;
	float min;

	for(it = this->Vertices.begin();
		it < this->Vertices.end();
		it++)
	{
		if(it == this->Vertices.begin())
		{
			min = (*it).z;
		}

		if(min > (*it).z)
		{
			min = (*it).z;
		}
	}

	return min;
}


CuboidCollisionComponent::CuboidCollisionComponent(Game* game, GameEntity* entity, CuboidPrism* boundingBox, bool active)
	: CollisionComponent(game, entity)
{
	this->_active = active;
	this->_boundingBox = boundingBox;

	CuboidCollisionComponent::_globalBoundingBoxes.push_back(this->_boundingBox);
}

D3DXVECTOR3 CuboidCollisionComponent::Position(void)
{
	return this->_entity->getPosition();
}

void CuboidCollisionComponent::Initialize(void)
{
}

void CuboidCollisionComponent::Update(GameEntity* entity, long time)
{
	if(this->_active)
	{
		vector<CuboidPrism*>::iterator it;
		float maxX = this->_boundingBox->MaxX() + this->Position().x;
		float maxY = this->_boundingBox->MaxY() + this->Position().y;
		float maxZ = this->_boundingBox->MaxZ() + this->Position().z;
		float minX = this->_boundingBox->MinX() + this->Position().x;
		float minY = this->_boundingBox->MinY() + this->Position().y;
		float minZ = this->_boundingBox->MinZ() + this->Position().z;
		

		for(it = this->_globalBoundingBoxes.begin();
			it < this->_globalBoundingBoxes.end();
			it++)
		{
			if(*it != this->_boundingBox)
			{
				if(	(maxX >= (*it)->MinX() && minX <= (*it)->MaxX()) &&
					(maxY >= (*it)->MinY() && minY <= (*it)->MaxY()) &&
					(maxZ >= (*it)->MinZ() && minZ <= (*it)->MaxZ())) 
				{
					float length = maxY - minY;
					D3DXVECTOR3 curPos = this->_entity->getPosition();

					if(maxY < (*it)->MaxY())	//right collision
					{
						curPos.y = (*it)->MinY()-length/2;
					}
					else	//left collision
					{
						curPos.y = (*it)->MaxY()+length/2;
					}
				
					this->_entity->setPosition(curPos);
				}
			}
		}	
	}
}

string CuboidCollisionComponent::GetName(void)
{
	return "CuboidCollisionComponent";
}