#pragma once
#include <string>
#include <vector>
#include <SFML\Graphics\Drawable.hpp>
#include "utils\header\utils.hpp"


namespace visualization 
{
	class Layer;
	class Visualizable;

	using LayerPtr = utils::SharedPointerDefition<Layer>;
	using VisualizablePtr = utils::SharedPointerDefition<Visualizable>;


	/**
    @brief This class is an interface for anything that needs to be visual on screen.
	Reference your object in this class to make it appear.
	**/
	class Visualizer : public sf::Drawable
	{
	public:
		using Ptr = utils::SharedPointerDefition<Visualizer>;
	private:
		// TODO 
		// AssetManager 
		// Reference to all visual resources like images
		
		// TODO 
		// Layers that hold objects to draw
	protected:
		std::vector<LayerPtr::Shared> my_layers;
	public:
		Visualizer();
		virtual ~Visualizer();

		/**
		@brief Draws all layers on the screen.
		**/
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		void add_element_to_all(VisualizablePtr::Shared element);
		void remove_element_from_all(VisualizablePtr::Shared element);
		void add_layer(LayerPtr::Shared layer);
		void remove_layer(LayerPtr::Shared layer);
		LayerPtr::Shared get_layer_by_name(const std::string &name) const;
	private:

	};
}
