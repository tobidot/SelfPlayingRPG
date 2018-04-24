#include "Object.h"
#include <boost\property_tree\ptree.hpp>
#include <sfml\Graphics\Sprite.hpp>
#include "asset_manager\header\AssetManager.h"

namespace game
{
	Object::Object()
	{

	}
	
	Object::~Object()
	{
	}

	void Object::update(float deltaTime)
	{
		on_update(deltaTime);
	}
}
