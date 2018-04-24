#pragma once
#include "utils\header\utils.hpp"

namespace sf
{
	class Sprite;
	using SpritePtr = utils::SharedPointerDefition<Sprite>;
}

namespace visualization
{
	class Layer;

	class Visualizable
	{
	public:
		using Ptr = utils::SharedPointerDefition<Visualizable>;
	public:
		virtual sf::SpritePtr::Shared get_sprite(const Layer &layer) const = 0;
		/// gets called right before drawing
		virtual void on_before_draw(const Layer &layer) {};
		/// gets called right after drawing
		virtual void on_after_draw(const Layer &layer) {};
	private:
	};
}