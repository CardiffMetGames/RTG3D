#pragma once
#include "cLight.h"
class DirectionLight :
	public cLight
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

