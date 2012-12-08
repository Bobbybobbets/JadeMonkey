#pragma once
#include <string>
#include <map>
#include <d3dx9.h>

using namespace std;

static class RessourceManager
{
public:
	static void LoadTexture(IDirect3DDevice9* d3ddev, string path);
	static LPDIRECT3DTEXTURE9 GetTexture(IDirect3DDevice9* d3ddev, string path);

private:
	static map<string, LPDIRECT3DTEXTURE9> _textureMap;
};