#pragma once
#include <sfml\System\Vector2.hpp>
#include "utils\header\SharedPointerDefintion.h"
#include "utils\header\ToString.h"


namespace utils
{
	template<typename T>
	struct Point
	{
	private:
		using SelfType = Point<T>;
	public:
		using Ptr = SharedPointerDefition<SelfType>;
	public:
		T x, y;
	public:
		Point(const T& x = 0, const T& y = 0)
		{
			this->x = x;
			this->y = y;
		}
		template<typename R>
		Point(const R& x = 0, const R& y = 0)
		{
			this->x = static_cast<const T>(x);
			this->y = static_cast<const T>(y);
		}
		operator sf::Vector2<T>()
		{
			return sf::Vector2<T>(x, y);
		}
	};

	/*
	template<typename T>
	struct Stringify<const Point<T> &, void>
	{
		static std::string to_string(const Point<T> &p)
		{
			std::stringstream stream;
			stream << "Point(" << to_string(p.x) << ", " << to_string(p.y) << ")";
			return stream.str();
		}
	};
	*/


	template<typename T>
	inline std::string to_debug_string(Point<T> &p)
	{
		std::stringstream stream;
		stream << "Point( "  << p.x << ", " << p.y << ")";
		return stream.str();
	}
	

	template<typename T>
	using PointPtr = typename Point<T>::Ptr;
}


namespace std
{
	template<typename T>
	inline string to_string(const utils::Point<T> &p)
	{
		std::stringstream stream;
		stream << "(" << to_string(p.x) << ", " << to_string(p.y) << ")";
		return stream.str();
	}
}
