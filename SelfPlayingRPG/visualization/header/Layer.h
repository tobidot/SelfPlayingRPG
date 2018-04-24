#pragma once

#include <string>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\Graphics\View.hpp>
#include "utils\header\utils.hpp"
#include "Visualizable.h"

namespace sf
{
	class RenderTaret;

}


namespace visualization
{
	class Visualizable;
	using VisualizablePtr = utils::SharedPointerDefition<Visualizable>;

	class Layer : public sf::Drawable
	{
	public:
		using Ptr = utils::SharedPointerDefition<Layer>;
	private:
		int my_priority;
		std::string my_name;
		sf::View my_view;
	protected:
		std::vector<Visualizable::Ptr::Shared> my_elements;
	public:
		Layer(const std::string name, int prioritiy);
		virtual ~Layer();
	
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void on_change();
	
		void add_element(VisualizablePtr::Shared element);
		void remove_element(VisualizablePtr::Shared element);

		void set_view(const sf::View &view) { my_view = view; }
		sf::View get_view() const { return my_view; }
		const std::string &get_name() const { return my_name; }
		int get_priority() const { return my_priority; }

	private:

	};
}
