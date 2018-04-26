#pragma once
#include <string>
#include <type_traits>
#include <memory>
#include "utils\header\utils.hpp"
#include "visualization\header\Visualizer.h"
#include "exceptions\header\GameExceptions.h"
#include "asset_manager\header\AssetManager.h"
#include "utils\header\NovoTree.h"


namespace sf
{
	class RenderWindow;
	using RenderWindowPtr = utils::SharedPointerDefition<RenderWindow>;
}

namespace assets
{
	class AssetManager;
	using AssetManagerPtr = utils::SharedPointerDefition<AssetManager>;
}

namespace visualization
{
	class Visualizer;
	using VisualizerPtr = utils::SharedPointerDefition<Visualizer>;
}

namespace game
{
	class Object;
	class Doodad;
	class Monster;
	class Character;
	using ObjectPtr = utils::SharedPointerDefition<Object>;
	using DoodadPtr = utils::SharedPointerDefition<Doodad>;
	using MonsterPtr = utils::SharedPointerDefition<Monster>;
	using CharacterPtr = utils::SharedPointerDefition<Character>;

	class Application
	{
	public:
		using Ptr = utils::SharedPointerDefition<Application>;
		using NovoTree = utils::NovoTree < ObjectPtr::Shared, 64 >;

	private:
		sf::RenderWindowPtr::Unique my_window;
		assets::AssetManagerPtr::Unique my_asset_manager;
		visualization::VisualizerPtr::Unique my_visualizer;
		std::vector<ObjectPtr::Shared> my_game_objects; 
		std::shared_ptr<NovoTree> my_world = nullptr;
	public:
		Application(int width, int height, const std::string &label, const std::string &resourceList = "assets/ResourceList.json");
		~Application();
		void run();
		ObjectPtr::Shared create_object(std::string typeID);
		DoodadPtr::Shared create_doodad(std::string typeID);
		MonsterPtr::Shared create_monster(std::string typeID);
		CharacterPtr::Shared create_character(std::string typeID);

	private:
		template<typename T>
		std::shared_ptr<T> create_object(std::string typeID)
		{
			try
			{
				static_assert(std::is_base_of<Object, T>::value, "Cannot create an object wich is not derived from game::Object");
				auto object = std::make_shared<T>();
				if (!object) throw exceptions::game::CouldNotCreateObject();
				return object;
			}
			catch (boost::exception &e)
			{
				e << exceptions::game::Info_BlueprintID(typeID);
				throw;
			}
		};
	};

	using ApplicationPtr = utils::SharedPointerDefition<Application>;

}