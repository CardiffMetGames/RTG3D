#pragma once

#include "core.h"

class Cube {

private:

	GLuint				numFaces = 0;
	GLuint				vao = 0;

	GLuint					vertexBuffer;
	GLuint					colourBuffer;
	GLuint					indexBuffer;



public:

	Cube();
	~Cube();

	void render();
};