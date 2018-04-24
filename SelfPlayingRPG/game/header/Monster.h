#pragma once
#include "utils\header\SharedPointerDefintion.h"
#include "game\header\Object.h"

namespace game
{
	class Monster : public Object
	{
	public:
		using Ptr = utils::SharedPointerDefition<Monster>;
	public:
		Monster();
		virtual ~Monster();


		// Geerbt über Object
		virtual sf::SpritePtr::Shared get_sprite(const visualization::Layer & layer) const override;

		virtual void on_update(float deltaTime) override;


		// Geerbt über Object
		virtual void init_from_blueprint(const assets::AssetManager & assetManager, const boost::property_tree::ptree & bluePrint) override;

	};

	using MonsterPtr = utils::SharedPointerDefition<Monster>;
}
