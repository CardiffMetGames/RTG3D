#include "GameObjectFactory.h"
#include "GameObject.h"
#include <assert.h>

using std::string;

GameObject* GameObjectFactory::makeNewGO(string _type)
{
	printf("GAME OBJECT TYPE: %s \n", _type.c_str());
	if (_type == "GAME_OBJECT")
	{
		return new GameObject();
	}
	else
	{
		printf("UNKNOWN GAME OBJECT TYPE: %s \n", _type.c_str());
		assert(0);
		return nullptr;
	}
}
