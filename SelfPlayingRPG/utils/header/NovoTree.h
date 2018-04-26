#pragma once
#include <assert.h>
#include <string>
#include <array>
#include <vector>
#include <functional>
#include <numeric>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Vector2.hpp>
#include "SharedPointerDefintion.h"
#include "utils\header\Bounds.h"
#include "utils\header\Point.h"


namespace utils
{
	
	template<typename _ELEMENT, size_t _ELEMENT_THRESHOLD = 16, typename _GET_POS_FUNCTION = std::function<Point<float>(const _ELEMENT &e)> >
	class NovoTree
	{
	public:
		using SelfType = NovoTree < _ELEMENT, _ELEMENT_THRESHOLD, _GET_POS_FUNCTION>;
		using Ptr = utils::SharedPointerDefition<SelfType>;
		using ELEMENT = _ELEMENT;
		const static size_t ELEMENT_THRESHOLD = _ELEMENT_THRESHOLD;
		//const static size_t MAX_DEPTH = _MAX_DEPTH;
		using GET_POS_FUNCTION = _GET_POS_FUNCTION;
		using ChildType = NovoTree <ELEMENT, ELEMENT_THRESHOLD, GET_POS_FUNCTION>;
		using ChildList = std::array<std::shared_ptr<ChildType>, 16>;
		using ChildListPtr = std::shared_ptr<ChildList>;
		using ElementList = std::vector<ELEMENT>;
		using ElementListPtr = std::shared_ptr<ElementList>;
		using Bounds = utils::Bounds<float>;
		enum ChildID
		{// Bits == left X, right X, down Y, up Y
			Middle = 0b0000,
			Up = 0b0001,
			UpRight = 0b0101,
			Right = 0b0100,
			DownRight = 0b0110,
			Down = 0b0010,
			DownLeft = 0b1010,
			Left = 0b1000,
			UpLeft = 0b1001
		};
	private:
		const Bounds my_bounds;
		const Bounds my_middle_child_bounds;
		const GET_POS_FUNCTION my_get_position_of;
		const size_t my_max_depth;
		SelfType *my_parent = nullptr;
		ChildListPtr my_children = nullptr;
		ElementListPtr my_elements = std::make_shared<ElementList>();
	public:
		NovoTree(const Bounds &bounds, const GET_POS_FUNCTION &getPositionOf, SelfType *parent, const size_t maxDepth = 16) :
			my_bounds(bounds),
			my_middle_child_bounds(
			(bounds.left * 2 + bounds.right) / 3,
				(bounds.top * 2 + bounds.bottom) / 3,
				(bounds.left + bounds.right * 2) / 3,
				(bounds.top + bounds.bottom * 2) / 3
			),
			my_get_position_of(getPositionOf),
			my_parent(parent),
			my_max_depth(maxDepth)
		{
		};

		/**
		@return the node that took @p element
		**/
		SelfType *insert(const ELEMENT &element)
		{
			Point<float> position = my_get_position_of(element);
			if (contains(position))
			{
				if (has_children())
				{
					auto childID = get_childID_for(position);
					auto child = (*my_children)[childID];
					assert(child);
					return child->insert(element);
				}
				else
				{
					my_elements->push_back(element);
					if ( my_elements->size() > ELEMENT_THRESHOLD && my_max_depth > 1 ) divide();
				}
				return this;
			}
			return nullptr;
		};

		bool contains(const ELEMENT &element) const
		{
			const sf::Vector2f position = my_get_position_of(element);
			return (position.x >= my_bounds.left && position.x < my_bounds.right &&
				position.y >= my_bounds.top && position.y < my_bounds.bottom);
		}
		bool contains(const sf::Vector2f &position) const
		{
			return (position.x >= my_bounds.left && position.x < my_bounds.right &&
				position.y >= my_bounds.top && position.y < my_bounds.bottom);
		}
		ElementListPtr pick_within(const Bounds &bounds, ElementListPtr out = nullptr) const
		{
			return out;
		}
		ElementListPtr pick_all(ElementListPtr out = nullptr) const
		{
			for (auto *child : my_children)
			{
				if (child)
				{
					out->append(child->pick_all());
				}
			}
			return out;
		}

		size_t count_elements() const
		{
			if (has_children())
			{
				return std::reduce(my_children->begin(), my_children->end(), 0ull, [](size_t acc, std::shared_ptr<ChildType> child ) {
					if (!child) return acc;
					return acc + child->count_elements();					
				});
			}
			else
			{
				return my_elements ? my_elements->size() : 0;
			}
		}

		void divide()
		{
			// create children
			my_children = std::make_shared<ChildList>();
			assert(my_children);
			const float childWidth = (my_bounds.right - my_bounds.left) / 3;
			const float childHeight = (my_bounds.bottom - my_bounds.top) / 3;
			const float centerX = (my_bounds.right + my_bounds.left) / 2;
			const float centerY = (my_bounds.bottom + my_bounds.top) / 2;
			for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j)
			{
				auto bounds = utils::Bounds<float>(
					my_bounds.left + childWidth * (i),
					my_bounds.top + childHeight * (j),
					my_bounds.left + childWidth * (i + 1),
					my_bounds.top + childHeight * (j + 1)
					);
				auto pos = bounds.center();
				ChildID childID = get_childID_for(pos);
				my_children->at(childID) = std::make_shared<ChildType>(bounds, my_get_position_of, this, my_max_depth - 1);
			}
			// resinsert all elements
			while (my_elements->empty() == false)
			{
				auto &e = my_elements->back();
				insert(e);
				my_elements->pop_back();
			}
			// destroy element list
			my_elements.reset();
		}
		std::string to_string(const std::string &indent = "") const
		{
			std::stringstream stream;
			const string typeIndent = indent + "| ";
			const string enumIndent = indent + "|----";
			const string childIndent = indent + "|    ";
			stream << indent << std::to_string(my_bounds) << endl;
			if (has_children())
			{
				stream << typeIndent << "Children:" << std::endl;
				for (auto child : *my_children)
				{
					if (child && ( child->has_elements() || child->has_children() ) ) stream << child->to_string(childIndent);
				}
			}
			else
			{
				stream << typeIndent << "Elements: (" << my_elements->size() << ")" << std::endl;
				for (auto elem : *my_elements)
				{
					stream << enumIndent << std::to_string(elem) << std::endl;
				}
			}
			return stream.str();
		}

		inline bool is_root() const { return my_parent == nullptr; }
		inline SelfType *get_parent() const { return my_parent; }
		inline bool has_children() const { return my_children.get() != nullptr; };
		inline bool has_elements() const { return my_elements.get() != nullptr && my_elements->empty() == false; };
	private:
		ChildID get_childID_for(utils::Point<float> p) const
		{
			bool left = p.x < my_middle_child_bounds.left;
			bool right = p.x >= my_middle_child_bounds.right;
			bool top = p.y < my_middle_child_bounds.top;
			bool bottom = p.y >= my_middle_child_bounds.bottom;
			return static_cast<ChildID>((left << 3) + (right << 2) + (top << 1) + (bottom));
		}

		
	public:

	};
	
	template<typename ELEMENT, size_t ELEMENT_THRESHOLD, typename GET_POSITION>
	using Ptr = utils::SharedPointerDefition<NovoTree<ELEMENT, ELEMENT_THRESHOLD, GET_POSITION>>;
	
}


namespace std
{
	template<typename ELEMENT, size_t ELEMENT_THRESHOLD, typename GET_FUNC>
	inline string to_string(utils::NovoTree<ELEMENT, ELEMENT_THRESHOLD, GET_FUNC> &tree)
	{
		std::stringstream stream;
		stream << "NovoTree " << endl << tree.to_string("");
		return stream.str();
	}
}