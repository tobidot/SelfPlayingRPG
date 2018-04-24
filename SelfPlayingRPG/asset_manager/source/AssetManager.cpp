#include <string>
#include <iostream>
#include <SFML\Graphics.hpp>
#include <boost\exception\all.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../header/AssetManager.h"
#include "exceptions\header\AssetManagerExceptions.h"

using namespace std::literals::string_literals;

namespace assets
{
	AssetManager::AssetManager()
	{
		my_data_tree = std::make_shared<boost::property_tree::ptree>();
	}

	AssetManager::~AssetManager()
	{

	}

	std::string AssetManager::add_texture(sf::TexturePtr::Shared texture, const std::string &id)
	{
		std::string nameID = (id == "") ? ("@"s) + std::to_string(my_next_resource_id): id;
		auto result = my_textures.emplace(id, texture);
		if (!result.second) BOOST_THROW_EXCEPTION( exceptions::assets::ResourceAlreadyExists() << exceptions::assets::Info_ResourceID(id) );
		++my_next_resource_id;
		return id;
	}

	std::string AssetManager::add_texture(const std::string &fileName, const std::string &id)
	{
		sf::TexturePtr::Shared texture = std::make_shared<sf::Texture>();
		if ( texture->loadFromFile(fileName) ) return add_texture(texture, id);
		BOOST_THROW_EXCEPTION( exceptions::assets::FileNotFound() << exceptions::assets::Info_FileName(fileName) << exceptions::assets::Info_ResourceID(id) );
	}

	const boost::property_tree::ptree & AssetManager::get_json(const std::string & path) const
	{
		auto data = my_data_tree->get_child_optional(path);
		if (!data) BOOST_THROW_EXCEPTION(exceptions::assets::NoSuchResource() << exceptions::assets::Info_ResourceID(path));
		return *data;
	}

	sf::TexturePtr::Shared AssetManager::get_texture(const std::string & id) const
	{
		auto it = my_textures.find(id);
		if (it == my_textures.end()) BOOST_THROW_EXCEPTION( exceptions::assets::NoSuchResource() << exceptions::assets::Info_ResourceID(id) );
		return it->second;
	}

	size_t AssetManager::load_resources(const std::string &resourceListFileName)
	{
		auto countResources = 0ull;
		auto root = boost::property_tree::ptree();
		boost::property_tree::read_json(resourceListFileName, root);
		for (auto &imageRC : root.get_child("images"))
		{
			auto &image = imageRC.second;
			auto &id = image.get<std::string>("id");
			auto &fileName = image.get<std::string>("file");
			add_texture(fileName, id);
			++countResources;
		}
		for (auto &jsonRC : root.get_child("jsons"))
		{
			auto &fileName = jsonRC.second.get_value<std::string>();
			add_json(fileName);
			++countResources;
		}
		return countResources;
	}

	void AssetManager::add_json(const std::string & fileName, const std::string &path)
	{
		boost::property_tree::ptree root;
		boost::property_tree::read_json(fileName, root);
		add_json(root, path);
	}

	void AssetManager::add_json(const boost::property_tree::ptree &data, const std::string &path)
	{
		auto &root = my_data_tree->get_child(path);
		for (auto &childPair : data)
		{
			auto &id = childPair.first;
			auto &child = childPair.second;
			if (root.get_child_optional(id))
			{
				auto newPath = ((path.empty())?"":path + '.') + id;
				add_json(child, path);
			}
			else
			{
				root.add_child(id, child);
			}
		}
	}

}