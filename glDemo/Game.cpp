#include "Game.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include <assert.h>

Game::Game()
{
}

//tick all my Game Objects
//the window is being passed in to allow things liek keyboard control of your player character
void Game::Update(GLFWwindow* _window)
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		(*it)->Tick(_window);
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


//don't like this being here but..
void Game::RenderMeshes(class cCamera* _cam, cScene* _scene)
{
	for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
	}
}
