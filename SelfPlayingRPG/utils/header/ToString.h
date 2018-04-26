#pragma once
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include "boost\core\enable_if.hpp"


namespace utils
{
	/**
	TODO 
	Not realy sure where to go with this
	**/ 


	template<typename T> inline
		typename std::enable_if<std::is_integral<T>::value, std::string>::type
		to_debug_string(T x)
	{
		return std::string("Int#") + std::to_string(x);
	}

	template<typename T> inline
		typename std::enable_if<std::is_floating_point<T>::value, std::string>::type
		to_debug_string(T x)
	{
		return std::string("Float#") + std::to_string(x);
	}

	template<typename T> inline
		typename std::enable_if<std::is_pointer<T>::value, std::string>::type
		to_debug_string(T x)
	{
		std::stringstream stream;
		stream << "Ptr@";
		if (x) stream << std::hex << (size_t)x << " -> " << to_debug_string(*x);
		else stream << "__null__";
		return stream.str();
	}

	template<typename T> inline
		typename std::enable_if<std::is_class<T>::value, std::string>::type
		to_debug_string(T &x)
	{
		std::stringstream stream;
		stream << "Class@" << std::hex << (size_t)&x; 
		return stream.str();
	}

	template<typename T> inline
		std::string	to_debug_string(std::shared_ptr<T> ptr)
	{
		std::stringstream stream;
		stream << "Shared_" << to_debug_string(ptr.get());
		return stream.str();
	}

	template<typename T> inline
		std::string	to_debug_string(std::weak_ptr<T> ptr)
	{
		std::stringstream stream;
		stream << "Weak_";
		if (auto sp = ptr.lock()) stream << to_debug_string(sp.get());
		else stream << "*No Ref*";
		return stream.str();
	}
	
	template<typename T> inline
		std::string	to_debug_string(std::unique_ptr<T> ptr)
	{
		std::stringstream stream;
		stream << "Unique_" << to_debug_string(ptr.get());
		return stream.str();
	}

	inline std::string to_debug_string(bool b)
	{
		return std::string("Bool#") + std::string(b?"True":"False");
	}
}