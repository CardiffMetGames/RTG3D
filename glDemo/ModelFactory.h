#pragma once
#include <string>
class Model;

class ModelFactory
{
public:

	static Model* makeNewModel(std::string _type);
};

