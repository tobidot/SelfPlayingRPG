#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <boost\property_tree\ptree.hpp>
#include "utils\header\utils.hpp"

namespace sf
{
	class Texture;
	using TexturePtr = utils::SharedPointerDefition<Texture>;
}

namespace boost
{
	namespace property_tree
	{
		using ptreePtr = utils::SharedPointerDefition<ptree>;
	}
}

namespace assets
{


	class AssetManager
	{
	public:
		using Ptr = utils::SharedPointerDefition<AssetManager>;
	private:
	private:
		boost::property_tree::ptreePtr::Shared my_data_tree = nullptr;
		std::unordered_map<std::string, sf::TexturePtr::Shared> my_textures;
		unsigned long my_next_resource_id = 0;
	public:
		AssetManager();
		~AssetManager();

		/// @return the amount of resources loaded
		size_t load_resources(const std::string &resourceListFileName);
		inline void add_json(const char *fileName, const std::string &path = "") { add_json(std::string(fileName)); };
		void add_json(const std::string &fileName, const std::string &path = "");
		void add_json(const boost::property_tree::ptree &data, const std::string &path = "");
		std::string add_texture(sf::TexturePtr::Shared texture, const std::string &id = "");
		std::string add_texture(const std::string &fileName, const std::string &id = "");

		const boost::property_tree::ptree &get_json(const std::string &path) const;
		sf::TexturePtr::Shared get_texture(const std::string &id) const;
	public:
	};

}