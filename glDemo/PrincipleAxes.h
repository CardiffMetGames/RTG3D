#pragma once

#include "core.h"



class CGPrincipleAxes  {

private:

	GLuint				numFaces = 0;
	GLuint				vao = 0;

	GLuint					vertexBuffer;
	GLuint					colourBuffer;
	GLuint					indexBuffer;

public:

	CGPrincipleAxes();
	~CGPrincipleAxes();

	void render(bool showZAxis = true);
};
