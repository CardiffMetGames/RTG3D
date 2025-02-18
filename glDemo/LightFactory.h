#pragma once
#include <string>
class Light;

//ditto for the other factory but now for lights!
class LightFactory
{
public:

	static Light* makeNewLight(std::string _type);
};

