#pragma once

#include <string>
#include <unordered_map>
#include <map>

namespace Rest
{
    using Headers = std::unordered_map<std::string, std::string>;
    using Parameters = std::map<std::string, std::string>;

	struct HTTP
	{
		using Method = std::string;
		using ResponseCode = unsigned short;

		static const Method GET;
		static const Method POST;
	};
}
