#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "visualization\header\Sprite.h"
#include "visualization\header\Layer.h"
#include "visualization\header\Visualizer.h"
#include "asset_manager\header\AssetManager.h"

using namespace visualization;

namespace tests
{
	int draw_sprite();
	int draw_layer();
	int draw_visualizer();

	/**
	@brief Draw a simple sprite.	 
	**/
	int draw_sprite()
	{
		std::cout << "Run Test : Draw Sprite" << std::endl;
		sf::TexturePtr::Shared texture = std::make_shared<sf::Texture>();
		texture->loadFromFile("assets\\images\\test.bmp");
		visualization::Sprite sprite(texture);
		sprite.get_sprite()->setColor(sf::Color(100,100,100));
		sprite.get_sprite()->setPosition(0,0);
		sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(*sprite.get_sprite());
			window.display();
		}
		return 0;
	}


	/**
	@brief Draw a layer with several sprites.
	**/
	int draw_layer()
	{
		std::cout << "Run Test : Draw Layer" << std::endl;
		sf::View view;
		visualization::Layer::Ptr::Shared layer = std::make_shared<visualization::Layer>("Game", 0);
		view = sf::View(sf::Vector2f(200, 200), sf::Vector2f(800, 400));
		view.setViewport(sf::FloatRect(0, 0, 1, 0.5));
		layer->set_view( view );
		visualization::Layer::Ptr::Shared layer2 = std::make_shared<visualization::Layer>("Interface", 0);
		view = sf::View(sf::Vector2f(100, 100), sf::Vector2f(200, 100));
		view.setViewport(sf::FloatRect(0, 0.5f, 1, 0.5f));
		layer2->set_view(view);
		// TODO 
		// layer set size
		sf::TexturePtr::Shared texture = std::make_shared<sf::Texture>();
		texture->loadFromFile("assets\\images\\test.bmp");
		sf::TexturePtr::Shared texture2 = std::make_shared<sf::Texture>();
		texture2->loadFromFile("assets\\images\\test2.bmp");
		{
			std::vector<visualization::Sprite::Ptr::Shared> sprites;
			for (size_t i = 0; i < 5; i++)
			{
				Sprite::Ptr::Shared sprite = std::make_shared<Sprite>(texture2);
				sprite->get_sprite()->setPosition((float)(rand() % 200), (float)(rand() % 200));
				//sprite.setPosition(200, 200);
				layer->add_element(sprite);
			}
		}
		layer2->add_element(std::make_shared<Sprite>(texture));
		sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(*layer);
			window.draw(*layer2);
			window.display();
		}
		return 0;
	}

	/**
	Test showing potenital of Layers for a minimap
	**/
	int draw_visualizer()
	{
		std::cout << "Run Test : Draw Visualizer" << std::endl;
		Visualizer visualizer;
		sf::View view;
		visualization::Layer::Ptr::Shared gameLayer = std::make_shared<visualization::Layer>("Game", 0);
		view = sf::View(sf::Vector2f(250, 250), sf::Vector2f(500, 500));
		view.setViewport(sf::FloatRect(0, 0, 1, 1));
		gameLayer->set_view(view);
		visualization::Layer::Ptr::Shared miniMapLayer = std::make_shared<visualization::Layer>("MiniMap", 0);
		view = sf::View(sf::Vector2f(1000, 1000), sf::Vector2f(2000, 2000));
		view.setViewport(sf::FloatRect(0.75f, 0.75f, 0.35f, 0.25f));
		miniMapLayer->set_view(view);
		visualizer.add_layer(gameLayer);
		visualizer.add_layer(miniMapLayer);

		sf::TexturePtr::Shared texture = std::make_shared<sf::Texture>();
		texture->loadFromFile("assets\\images\\test.png");
		{
			std::vector<visualization::Sprite::Ptr::Shared> sprites;
			for (size_t i = 0; i < 50; i++)
			{
				Sprite::Ptr::Shared sprite = std::make_shared<Sprite>(texture);
				const sf::IntRect &textureRect = sprite->get_sprite()->getTextureRect();
				sprite->get_sprite()->setPosition((float)(rand() % 2000), (float)(rand() % 2000));
				sprite->get_sprite()->setOrigin((float)textureRect.width, (float)textureRect.height );
				gameLayer->add_element(sprite);
				miniMapLayer->add_element(sprite);
			}
		}
		sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(visualizer);
			window.display();
		}
		return 0;
	}

	int draw_resources()
	{
		std::cout << "Test : draw resources" << std::endl;
		assets::AssetManager assetManager;
		auto count = assetManager.load_resources("assets/ResourceList.json");

		Visualizer visualizer;
		sf::View view;
		visualization::Layer::Ptr::Shared gameLayer = std::make_shared<visualization::Layer>("Game", 0);
		view = sf::View(sf::Vector2f(250, 250), sf::Vector2f(500, 500));
		view.setViewport(sf::FloatRect(0, 0, 1, 1));
		gameLayer->set_view(view);
		visualizer.add_layer(gameLayer);

		sf::TexturePtr::Shared textures[2] = {
			assetManager.get_texture("test"), 
			assetManager.get_texture("test2")
		};
		{
			std::vector<visualization::Sprite::Ptr::Shared> sprites;
			for (size_t i = 0; i < 5; i++)
			{
				Sprite::Ptr::Shared sprite = std::make_shared<Sprite>(textures[rand()%2]);
				const sf::IntRect &textureRect = sprite->get_sprite()->getTextureRect();
				sprite->get_sprite()->setPosition((float)(rand() % 500), (float)(rand() % 500));
				sprite->get_sprite()->setOrigin((float)textureRect.width, (float)textureRect.height);
				gameLayer->add_element(sprite);
			}
		}
		sf::RenderWindow window(sf::VideoMode(800, 800), "Draw Resources");
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(visualizer);
			window.display();
		}
		return 0;
	}
}