#pragma once
#include "utils\header\utils.hpp"
#include "visualization\header\Visualizable.h"
#include <boost\property_tree\ptree_fwd.hpp>

namespace sf
{
	class Sprite;
}

namespace assets
{
	class AssetManager;
	using AssetManagerPtr = utils::SharedPointerDefition<AssetManager>;
}

namespace game
{
	class Application;

	class Object : public visualization::Visualizable
	{
		friend class Application;
	public:
		using Ptr = utils::SharedPointerDefition<Object>;
	private:
	protected:
	public:
		Object();
		virtual ~Object();

		void update(float deltaTime);
		virtual sf::SpritePtr::Shared get_sprite(const visualization::Layer &layer) const = 0;
		virtual void on_update(float deltaTime) = 0;

	private:
		virtual void init_from_blueprint(const assets::AssetManager &assetManager, const boost::property_tree::ptree &bluePrint) = 0;
	};

	using ObjectPtr = utils::SharedPointerDefition<Object>;
}