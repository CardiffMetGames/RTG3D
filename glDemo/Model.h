#pragma once
#include <string>

using namespace std;

class Model
{
public:
	Model();
	~Model();

	virtual void Load(ifstream& _file);
	virtual void Render() {};

	string GetName() { return m_name; }

protected:
	string m_name;
	string m_type;
};