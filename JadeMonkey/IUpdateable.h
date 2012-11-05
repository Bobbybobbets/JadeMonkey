#pragma once
class IUpdateable
{
public:
	virtual int Update(long time) = 0;
};