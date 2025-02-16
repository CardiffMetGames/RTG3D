#include "core.h"
#include "DirectionLight.h"
#include "helper.h"
#include "stringHelp.h"

DirectionLight::DirectionLight()
{
	m_type = "DIRECTION";
	m_pos = vec3(0.0, 0.0, 0.0);
	m_direction = vec3(0.0, 1.0, 0.0);
}

DirectionLight::~DirectionLight()
{
}

void DirectionLight::Load(ifstream& _file)
{
	cLight::Load(_file);
	StringHelp::Float3(_file, "DIRECTION", m_direction.x, m_direction.y, m_direction.z);
}

void DirectionLight::SetRenderValues(unsigned int _prog)
{
	cLight::SetRenderValues(_prog);

	GLint loc;
	string dirString = m_name + "Dir";

	if (Helper::SetUniformLocation(_prog, dirString.c_str(), &loc))
		glUniform3fv(loc, 1, glm::value_ptr(m_direction));
}
