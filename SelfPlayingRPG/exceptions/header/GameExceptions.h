#pragma once
#include <boost\exception\all.hpp>

namespace exceptions 
{
	namespace game
	{
		using Info_BlueprintID = boost::error_info<struct _Info_BluePrintID, std::string>;

		class CouldNotCreateObject : public virtual boost::exception, public virtual std::exception {};
	}

}