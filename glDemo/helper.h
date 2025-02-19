#pragma once
//a useful function that was needed in a few places, so made this mini-helper class
//it finds the location in the shader program of a given uniform variable
class Helper
{
public:

	static bool SetUniformLocation(unsigned int shader, const char* name, GLint* pLocation)

	{
		*pLocation = glGetUniformLocation(shader, name);

		return (*pLocation >= 0);
	}
};