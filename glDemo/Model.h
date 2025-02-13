#pragma once
#include <string>

using namespace std;

class Model
{
public:
	Model();
	~Model();

	virtual void Load(ifstream& _file);

protected:
	string m_name;
	string m_type;
};