#pragma once
#include "core.h"
#include <stdio.h>
#include <string>
#include "RenderPass.h"

using namespace std;
class Scene;

using namespace glm;

//Base class of a GameObject
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	//load me from the file
	virtual void Load(ifstream& _file);

	//update _window allows for Keyboard access
	virtual void Tick(float _dt);

	//render this object
	virtual void PreRender();
	virtual void Render();

	//various getters and setters
	void SetName(string _name) { m_name = _name; }
	string GetName() { return m_name; }
	GLuint GetShaderProg() { return m_ShaderProg; }

	virtual void Init(Scene* _game);

	RenderPass GetRP() { return m_RP; }

protected:

	string m_name;
	string m_type;

	vec3		m_pos;
	vec3		m_rot;		// current rotation angle used to Create the rotation matrix
	vec3		m_scale;
	vec3		m_rot_incr;		

	glm::mat4	m_worldMatrix;
	GLuint m_ShaderProg;

	RenderPass m_RP = RP_OPAQUE;
};

