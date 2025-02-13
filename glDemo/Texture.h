#pragma once
#include "core.h"
#include <string>

using namespace std;

class Texture
{
public:
	Texture(ifstream& _file);
	~Texture();

	GLuint GetTexID(){ return m_texID; }
	string GetName() { return m_name; }

protected:
	string m_name;
	GLuint m_texID;

};
