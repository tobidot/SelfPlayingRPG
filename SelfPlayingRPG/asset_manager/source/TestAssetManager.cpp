#include <string>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "asset_manager\header\AssetManager.h"
#include "exceptions\header\AssetManagerExceptions.h"

namespace pt = boost::property_tree;



namespace tests
{
	int read_json();
	int load_resources();

	int read_json()
	{
		std::cout << "Test : Read json" << std::endl;
		std::cout << "Prints the list of all resources." << std::endl << std::endl;
		pt::ptree root;
		pt::read_json("./assets/ResourceList.json", root);
		try
		{		
			for (auto &imageRC : root.get_child("images"))
			{
				auto &image = imageRC.second;
				std::cout << image.get<std::string>("id") << " : " << image.get<std::string>("file") << std::endl;
			}
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
			return -1;
		}
		getchar();
		return 0;
	}

	int load_resources()
	{
		int result = -1;
		std::cout << "Test : load resources" << std::endl;
		assets::AssetManager am;
		try
		{
			auto count = am.load_resources("./assets/ResourceList.json");
			std::cout << "Resources loaded : " << count << std::endl;
			result = 0;
		}
		catch (exceptions::assets::FileNotFound &e)
		{
			std::cout << "File not found : ";
			if ( std::string *s = boost::get_error_info<exceptions::assets::Info_FileName>(e) ) std::cout << *s;
			std::cout << std::endl;
		}

		getchar();
		return result;
	}


	
}