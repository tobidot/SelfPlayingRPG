#include "game\header\Monster.h"

namespace game
{
	Monster::Monster()
	{
	}
	
	Monster::~Monster()
	{
	}
	
	sf::SpritePtr::Shared Monster::get_sprite(const visualization::Layer & layer) const
	{
		return sf::SpritePtr::Shared();
	}

	void Monster::on_update(float deltaTime)
	{
	}

	void Monster::init_from_blueprint(const assets::AssetManager & assetManager, const boost::property_tree::ptree & bluePrint)
	{
	}
}