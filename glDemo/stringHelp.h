#pragma once
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class StringHelp {
public:

	static void String(ifstream& _file, string _message, string& _out)
	{
		string dummy;
		_file >> dummy >> _out; _file.ignore(255, '\n');
		cout << _message <<" : " << _out << endl;
	}

	static void Float3(ifstream& _file, string _message, float& _out1,float& _out2, float& _out3)
	{
		string dummy;
		_file >> dummy >> _out1 >> _out2 >> _out3; _file.ignore(255, '\n');
		cout << _message << " : " << _out1 <<" "<< _out2 <<" " << _out3 << endl;
	}

	static void Float(ifstream& _file, string _message, float& _out)
	{
		string dummy;
		_file >> dummy >> _out; _file.ignore(255, '\n');
		cout << _message << " : " << _out << endl;
	}
};
