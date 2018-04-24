#include <memory>
#include <SFML\Graphics.hpp>
#include "game\header\Application.h"
#include "game\header\Object.h"
#include "game\header\Doodad.h"
#include "game\header\Monster.h"
#include "game\header\Character.h"
#include "visualization\header\Visualizer.h"
#include "visualization\header\Layer.h"
#include "asset_manager\header\AssetManager.h"
#include "exceptions\header\AssetManagerExceptions.h"


namespace game
{
	Application::Application(int width, int height, const std::string &label, const std::string &resourceList) :
		my_window( new sf::RenderWindow(sf::VideoMode(width, height), label) ),
		my_visualizer( new visualization::Visualizer() ),
		my_asset_manager( new assets::AssetManager() )
	{
		my_asset_manager->load_resources(resourceList);
		my_visualizer->add_layer(std::make_shared<visualization::Layer>("Game", 0));
	}

	Application::~Application()
	{
		my_window->close();
	}

	void Application::run()
	{
		while (my_window->isOpen())
		{
			sf::Event event;
			while (my_window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					return;
			}
			my_window->clear();
			my_window->draw(*my_visualizer);
			my_window->display();
		}
	}

	ObjectPtr::Shared Application::create_object(std::string typeID)
	{
		auto type = typeID.substr(0, typeID.find('.'));
		Object::Ptr::Shared object = nullptr;
		if (type.compare("doodad") == 0) object = create_doodad(typeID);
		if (type.compare("monster") == 0) object = create_monster(typeID);
		if (type.compare("character") == 0) object = create_character(typeID);
		if (!object) BOOST_THROW_EXCEPTION(exceptions::game::CouldNotCreateObject() << exceptions::game::Info_BlueprintID(typeID) );
		object->init_from_blueprint((*my_asset_manager), my_asset_manager->get_json( typeID ) );
		my_visualizer->add_element_to_all(object);
		return object;
	}

	DoodadPtr::Shared Application::create_doodad(std::string typeID)
	{
		return create_object<Doodad>(typeID);
	}

	MonsterPtr::Shared Application::create_monster(std::string typeID)
	{
		return create_object<Monster>(typeID);
	}

	CharacterPtr::Shared Application::create_character(std::string typeID)
	{
		return create_object<Character>(typeID);
	}
}