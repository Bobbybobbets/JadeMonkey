#include "VectorUtil.h"
#include <math.h>

float VectorUtil::Distance3f(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2) + pow(v2.z - v1.z, 2));
}