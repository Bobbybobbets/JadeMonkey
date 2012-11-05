#pragma once
class IDrawable
{
public:
	virtual int LoadContent() = 0;
	virtual int Draw(long time) = 0;
};