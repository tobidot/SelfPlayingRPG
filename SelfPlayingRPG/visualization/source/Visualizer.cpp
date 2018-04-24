#include <SFML\Graphics.hpp>
#include "visualization\header\Visualizable.h"
#include "../header/Visualizer.h"
#include "../header/Layer.h"

namespace visualization
{
	Visualizer::Visualizer()
	{
	}

	Visualizer::~Visualizer()
	{

	}

	void Visualizer::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		for (auto layer : my_layers)
		{
			target.draw(*layer, states);
		}
	}

	void Visualizer::add_element_to_all(VisualizablePtr::Shared element)
	{
		for (auto layer : my_layers)
		{
			layer->add_element(element);
		}
	}

	void Visualizer::remove_element_from_all(VisualizablePtr::Shared element)
	{
		for (auto layer : my_layers)
		{
			layer->remove_element(element);
		}
	}

	void Visualizer::add_layer(LayerPtr::Shared layer)
	{
		my_layers.push_back(layer);
	}

	void Visualizer::remove_layer(LayerPtr::Shared layer)
	{
		auto it = std::find(my_layers.begin(), my_layers.end(), layer);
		if (it != my_layers.end()) my_layers.erase(it);
	}

	LayerPtr::Shared Visualizer::get_layer_by_name(const std::string & name) const
	{
		auto it = std::find_if(my_layers.begin(), my_layers.end(), [&name](Layer::Ptr::Shared layer){
			return layer->get_name().compare( name ) == 0;
		});
		return *it;
	}
}
