#pragma once
#include "Visualizable.h"
#include "utils\header\utils.hpp"

namespace sf
{
	class Sprite;
	class Image;
	class Texture;
	class RenderTarget;
	using SpritePtr = utils::SharedPointerDefition<Sprite>;
	using ImagePtr = utils::SharedPointerDefition<Image>;
	using TexturePtr = utils::SharedPointerDefition<Texture>;
	using RenderTargetPtr = utils::SharedPointerDefition<RenderTarget>;
}

namespace visualization
{
	class Layer;

	class Sprite : public visualization::Visualizable
	{
	public:
		using Ptr = utils::SharedPointerDefition<Sprite>;
	protected:
		sf::SpritePtr::Shared my_sprite;
	public:
		Sprite(const sf::TexturePtr::Shared image);
		virtual ~Sprite();

		virtual sf::SpritePtr::Shared get_sprite(const Layer &layer) const;
		sf::SpritePtr::Shared get_sprite();
	private:

	};

}