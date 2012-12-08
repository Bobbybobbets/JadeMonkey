#include "RessourceManager.h"

map<string, LPDIRECT3DTEXTURE9> RessourceManager::_textureMap;

void RessourceManager::LoadTexture(IDirect3DDevice9* d3ddev, string path)
{
	RessourceManager::_textureMap.insert(pair<string, LPDIRECT3DTEXTURE9>(path, nullptr));

	D3DXCreateTextureFromFile(
		d3ddev,
		path.c_str(),
		&RessourceManager::_textureMap[path]
	);
}

LPDIRECT3DTEXTURE9 RessourceManager::GetTexture(IDirect3DDevice9* d3ddev, string path)
{
	map<string, LPDIRECT3DTEXTURE9> m = RessourceManager::_textureMap;

	if(m.find(path) == m.end())
	{
		RessourceManager::LoadTexture(d3ddev, path);
	}

	return RessourceManager::_textureMap[path];
}