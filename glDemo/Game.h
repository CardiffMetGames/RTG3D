#pragma once
#include <list>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class GameObject;
class cScene;
struct GLFWwindow;
class cCamera;
class cLight;
class Model;
class Texture;
class Shader;

class Game
{
public:
	Game();
	//tick all GOs
	//_window allows for keyboard access
	void Update(float _dt);

	//add this GO to my list
	void AddGameObject(GameObject* _new);

	//return a pointer to a given GO by its name
	GameObject* GetGameObject(string _GOName);

	//Render Everything
	void Render();

	//load from file
	void Load(ifstream& _file);

protected:

	//data structure containing pointers to all my GameObjects
	int m_numCameras;
	int m_numLights;
	int m_numGameObjects;
	int m_numModels;
	int m_numTextures;
	int m_numShaders;
	std::list<cCamera*>    m_Cameras;
	std::list<cLight*>    m_Lights;
	std::list<Model*>		m_Models;
	std::list<Texture*>		m_Textures;
	std::list<Shader*>		m_Shaders;
	std::list<GameObject*> m_GameObjects;

};

