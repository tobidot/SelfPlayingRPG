#include <SFML\Graphics.hpp>
#include "visualization\header\Layer.h"


namespace visualization
{

	Layer::Layer(const std::string name, int prioritiy)
	{
		my_name = name;
		my_priority = prioritiy;
	}

	Layer::~Layer()
	{
	}

	void Layer::draw(sf::RenderTarget & target, sf::RenderStates states) const
	{
		sf::View parentView = target.getView();
		target.setView(my_view);
		for each (auto visual in my_elements)
		{
			visual->on_before_draw(*this);
			sf::Sprite &sprite = *visual->get_sprite(*this);
			target.draw(sprite,states);
			visual->on_after_draw(*this);
		}
		target.setView(parentView);
	}

	void Layer::on_change()
	{
	}

	void Layer::add_element(VisualizablePtr::Shared element)
	{
		my_elements.push_back(element);
		on_change();
	}

	void Layer::remove_element(VisualizablePtr::Shared element)
	{
		auto it = std::find(my_elements.begin(), my_elements.end(), element);
		if (it != my_elements.end() ) my_elements.erase(it);
		on_change();
	}
}
