#pragma once
#include <memory>
#include "utils\header\SharedPointerDefintion.h"
#include "game\header\Object.h"

namespace game
{
	class Doodad : public Object
	{
	public:
		using Ptr = utils::SharedPointerDefition<Doodad>;
	private:
		sf::SpritePtr::Shared my_sprite = std::make_shared<sf::Sprite>();
	public:
		Doodad();
		virtual ~Doodad();


		// Geerbt über Object
		virtual sf::SpritePtr::Shared get_sprite(const visualization::Layer & layer) const override;

		virtual void on_update(float deltaTime) override;

		// Geerbt über Object
		virtual void init_from_blueprint(const assets::AssetManager & assetManager, const boost::property_tree::ptree & bluePrint) override;
	};

	using DoodadPtr = utils::SharedPointerDefition<Doodad>;
}