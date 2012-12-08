#pragma once
#include "d3dx9.h"

static class VectorUtil
{
public:
	static float Distance3f(D3DXVECTOR3 v1, D3DXVECTOR3 v2);
	static bool PointInRect2f(D3DXVECTOR2 v, D3DRECT rect);
};