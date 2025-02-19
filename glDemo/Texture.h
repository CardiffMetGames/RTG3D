#pragma once
#include "core.h"
#include <string>

using namespace std;

//simple data structure that loads a texture using FreeImage
//from its description in the manifest and then links its GLuint handle to its name
class Texture
{
public:
	Texture(ifstream& _file);
	~Texture();

	GLuint GetTexID() { return m_texID; }
	string GetName() { return m_name; }

protected:
	string m_name;
	GLuint m_texID;

};
