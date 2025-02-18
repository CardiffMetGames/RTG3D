#pragma once
#include "Light.h"
class DirectionLight :
	public Light
{
public:
	DirectionLight();
	~DirectionLight();

	//load from manifest
	virtual void Load(ifstream& _file);

	//set render values
	virtual void SetRenderValues(unsigned int _prog);

protected:
	vec3 m_direction;

};

