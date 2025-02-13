#include "Game.h"
#include "GameObject.h"
#include "CameraFactory.h"
#include "cCamera.h"
#include "LightFactory.h"
#include "cLight.h"
#include "ModelFactory.h"
#include "model.h"
#include "GameObjectFactory.h"
#include <assert.h>

Game::Game()
{
}

//tick all my Game Objects
//the window is being passed in to allow things liek keyboard control of your player character
void Game::Update(float _dt)
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Tick(_dt);
	}
}

void Game::AddGameObject(GameObject* _new)
{
	m_GameObjects.push_back(_new);
}

//I want THAT Game Object by name
GameObject* Game::GetGameObject(string _GOName)
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->GetName() == _GOName)
		{
			return (*it);
		}
	}
	printf("Unknown Game Object NAME : %s \n", _GOName.c_str());
	assert(0);
	return nullptr;
}


//Render Everything
void Game::Render()
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Render();
	}
}

void Game::Load(ifstream& _file)
{
	string dummy;

	//load Cameras
	_file >> dummy >> m_numCameras; _file.ignore(256, '\n');
	cout << "CAMERAS : " << m_numCameras << endl;
	for (int i = 0; i < m_numCameras; i++)
	{
		//skip {
		_file.ignore(256, '\n');

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		cCamera* newCam = CameraFactory::makeNewCam(type);
		newCam->Load(_file);

		//skip }
		_file.ignore(256, '\n');
	}

	cout << endl << endl;

	//load Lights
	_file >> dummy >> m_numLights; _file.ignore(256, '\n');
	cout << "LIGHTS : " << m_numLights << endl;
	for (int i = 0; i < m_numLights; i++)
	{
		//skip {
		_file.ignore(256, '\n');

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		cLight* newLight = LightFactory::makeNewLight(type);
		newLight->Load(_file);

		//skip }
		_file.ignore(256, '\n');
	}

	cout << endl << endl;

	//load Modles
	_file >> dummy >> m_numModels; _file.ignore(256, '\n');
	cout << "LIGHTS : " << m_numModels << endl;
	for (int i = 0; i < m_numModels; i++)
	{
		//skip {
		_file.ignore(256, '\n');

		string type;
		_file >> dummy >> type; _file.ignore(256, '\n');
		Model* newModel = ModelFactory::makeNewModel(type);
		newModel->Load(_file);

		//skip }
		_file.ignore(256, '\n');
	}
}
