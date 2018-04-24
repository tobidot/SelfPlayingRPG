#pragma once
#include <memory>


namespace utils
{
	template<class CLASS>
	struct SharedPointerDefition
	{
		using Shared = std::shared_ptr<CLASS>;
		using Weak = std::weak_ptr<CLASS>;
		using Unique = std::unique_ptr<CLASS>;
	};
}