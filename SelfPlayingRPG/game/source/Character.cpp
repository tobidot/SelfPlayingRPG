#include "game\header\Character.h"

namespace game
{
	Character::Character()
	{
	}

	Character::~Character()
	{
	}

	sf::SpritePtr::Shared Character::get_sprite(const visualization::Layer & layer) const
	{
		return sf::SpritePtr::Shared();
	}

	void Character::on_update(float deltaTime)
	{
	}

	void Character::init_from_blueprint(const assets::AssetManager & assetManager, const boost::property_tree::ptree & bluePrint)
	{
	}
}