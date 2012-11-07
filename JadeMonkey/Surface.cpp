#include "Surface.h"
#include "jade_util.h"

Surface::Surface(int height , int width, Game *game): GameEntity(game)
{

}

Surface::~Surface()
{
		// releae the com objects
	COM_RELEASE(this->mVtxBuf);
	COM_RELEASE(this->mIndBuf);

	
}

int Surface::Initialize()
{
	// Initialize the vertext buffers and etc
	return 0;
}

int Surface::Draw(long time)
{
	return 0;
}

int Surface::Update(long time)
{
	return 0;
}

int Surface::LoadContent()
{
	return 0;
}