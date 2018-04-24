#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include "visualization\header\Sprite.h"


namespace visualization
{
	Sprite::Sprite(const sf::TexturePtr::Shared texture)
	{
		my_sprite = std::make_shared<sf::Sprite>();
		my_sprite->setTexture(*texture);
	}

	Sprite::~Sprite()
	{
	}

	sf::SpritePtr::Shared Sprite::get_sprite(const Layer &layer) const
	{
		return my_sprite;
	}

	sf::SpritePtr::Shared Sprite::get_sprite()
	{
		return my_sprite;
	}

}