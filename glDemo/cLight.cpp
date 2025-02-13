#include "core.h"
#include "cLight.h"

#include "helper.h"

cLight::cLight()
{
	m_type = "LIGHT";
	m_info.m_pos.x = 0.0f;
	m_info.m_pos.y = 0.0f;
	m_info.m_pos.z = 0.0f;
}

void cLight::Load(FILE* _fp)
{
	char buffer[256] = { "\0" };
	char primType[256] = { "\0" };
	fscanf_s(_fp, "%s%f%f%f", buffer, 256, &m_info.m_pos.x, &m_info.m_pos.y, &m_info.m_pos.z); // POS:	-25.0 0.0 20.0
	printf("POS: %f %f %f\n", m_info.m_pos.x, m_info.m_pos.y, m_info.m_pos.z);
	fscanf_s(_fp, "%s%f%f%f", buffer, 256, &m_info.m_col.x, &m_info.m_col.y, &m_info.m_col.z); // COL:	1.0 1.0 1.0
	printf("COL: %f %f %f\n", m_info.m_col.x, m_info.m_col.y, m_info.m_col.z);
	fscanf_s(_fp, "%s%f%f%f", buffer, 256, &m_info.m_att.x, &m_info.m_att.y, &m_info.m_att.z); // ATT:	1.0 0.5 0.2
	printf("ATT: %f %f %f\n", m_info.m_att.x, m_info.m_att.y, m_info.m_att.z);
	fscanf_s(_fp, "%s%f%f%f", buffer, 256, &m_info.m_amb.x, &m_info.m_amb.y, &m_info.m_amb.z); // AMB:	-25.0 0.0 20.0
	printf("AMB: %f %f %f\n", m_info.m_amb.x, m_info.m_amb.y, m_info.m_amb.z);
}

/////////////////////////////////////////////////////////////////////////////////////
// Update() - 
/////////////////////////////////////////////////////////////////////////////////////
void cLight::Update(GLFWwindow* _window)
{
}

//send values to the shaders to allow the use of this light
// <m_name>Pos <m_name>Col <m_name>Amb
void cLight::SetRenderValues(unsigned int _prog)
{
	GLint loc;
	string posString = m_name + "Pos";
	string colString = m_name + "Col";
	string ambString = m_name + "Amb";

	if (Helper::SetUniformLocation(_prog, posString.c_str(), &loc))
		glUniform3fv(loc, 1, glm::value_ptr(GetPos()));

	if (Helper::SetUniformLocation(_prog, colString.c_str(), &loc))
		glUniform3fv(loc, 1, glm::value_ptr(GetCol()));

	if (Helper::SetUniformLocation(_prog, ambString.c_str(), &loc))
		glUniform3fv(loc, 1, glm::value_ptr(GetAmb()));
}
