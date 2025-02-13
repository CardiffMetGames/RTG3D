#pragma once
#include "glm/glm.hpp"  
#include "glm/gtc/matrix_transform.hpp" 
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class cMesh;
struct GLFWwindow;

//base class for a light
class cLight
{
public:
	cLight();
	~cLight() {}

	void Init(float _x, float _y, float _z)
	{
		m_pos.x = _x;
		m_pos.y = _y;
		m_pos.z = _z;
	}

	//load from SDF
	virtual void Load(ifstream& _file);

	//tick this light
	//as for Game Objects bring in _window to allow for keyboard access
	virtual void Update(GLFWwindow* _window);

	//Getters and Setters
	void SetName(string _name) { m_name = _name; }
	string GetName() { return m_name; }
	void SetTye(string _type) { m_type = _type; }
	string GetType() { return m_type; }

	vec3 GetCol() { return m_col; }
	vec3 GetAmb() { return m_amb; }
	vec3 GetPos() { return m_pos; }

	//set my shader values
	//base version if name of light is LG
	//sets up shader values for LGpos LGcol & LGamb
	//position, main colour and ambient colour for this light
	virtual void SetRenderValues(unsigned int _prog);

protected:
	string m_name;
	string m_type;

	vec3 m_pos; // position of the light
	vec3 m_col; // colour of the light
	vec3 m_amb; // ambient colour of the light

};