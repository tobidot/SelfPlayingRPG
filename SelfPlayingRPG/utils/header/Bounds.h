#pragma once
#include "Point.h"
#include "utils\header\SharedPointerDefintion.h"

namespace utils
{
	template<typename T>
	struct Bounds
	{
	private:
		using SelfType = Bounds<T>;
	public:
		using Ptr = SharedPointerDefition<SelfType>;
	public:
		T left, right;
		T top, bottom;
	public:
		Bounds(const T &left, const T &top, const T &right, const T &bottom)
		{
			this->left = left;
			this->top = top;
			this->right = right;
			this->bottom = bottom;
		}
		Bounds(const Point<T> &topLeft, const Point<T> &bottomRight)
		{
			this->left = topLeft.x;
			this->top = topLeft.ytop;
			this->right = right;
			this->bottom = bottom;
		}
		Bounds(const sf::Rect<T> rect)
		{
			this->left = rect.top;
			this->top = rect.left;
			this->right = rect.top + rect.height;
			this->bottom = rect.left + rect.weight;
		}

		Point<T> center() const
		{
			return Point<T>((right + left) / 2, (top + bottom) / 2);
		}

		operator const sf::Rect<T> &()
		{
			return sf::Rect<T>{left, top, right - left, bottom - top};
		}
	};

	template<typename T>
	using BoundsPtr = typename Bounds<T>::Ptr;
}

namespace std
{
	template<typename T>
	inline string to_string(const utils::Bounds<T> &b)
	{
		std::stringstream stream;
		stream << "(< " << to_string(b.left) << ",^ " << to_string(b.top) << ",> " << to_string(b.right) << ",v " << to_string(b.bottom) << ")";
		return stream.str();
	}
}
