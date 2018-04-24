#include <boost\property_tree\ptree.hpp>
//#include <boost\property_tree\ptree.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include "game\header\Doodad.h"
#include "asset_manager\header\AssetManager.h"

namespace game
{
	Doodad::Doodad()
	{
		auto &textureRect = my_sprite->getTextureRect();
		my_sprite->setOrigin( (float)textureRect.width/2 , (float)textureRect.height / 2 );
	}

	Doodad::~Doodad()
	{
	}
	
	sf::SpritePtr::Shared Doodad::get_sprite(const visualization::Layer & layer) const
	{
		return my_sprite;
	}
	
	void Doodad::on_update(float deltaTime)
	{
	}

	void Doodad::init_from_blueprint(const assets::AssetManager & assetManager, const boost::property_tree::ptree & bluePrint)
	{
		if (auto imgName = bluePrint.get_optional<std::string>("image"))
		{
			my_sprite->setTexture( *assetManager.get_texture(*imgName) );
		}
		if (auto &sizeChild = bluePrint.get_child_optional("size"))
		{
			// TODO assert size has only 2 children
			const auto width = sizeChild.get().begin()->second.get_value<size_t>();
			const auto height = (sizeChild.get().begin()++)->second.get_value<size_t>();
			const auto &tRect = my_sprite->getTextureRect();
			my_sprite->setScale((float)width / tRect.width, (float)height / tRect.height);
		}
	}
}