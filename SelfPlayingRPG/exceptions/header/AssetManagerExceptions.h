#pragma once
#include <string>
#include <boost\exception\all.hpp>

namespace exceptions
{
	namespace assets
	{
		using Info_ResourceID = boost::error_info<struct _Info_ResourceID, std::string>;
		using Info_FileName = boost::error_info<struct _Info_FileName, std::string>;

		class FileNotFound : public virtual boost::exception, public virtual std::exception {};
		class NoSuchResource : public virtual boost::exception, public virtual std::exception {};
		class ResourceAlreadyExists : public virtual boost::exception, public virtual std::exception {};
	}
}