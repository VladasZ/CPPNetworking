#pragma once

#include <string>

#include "HTTP.h"

namespace Net
{
	struct Config
	{
		static std::string base_url;
		static Headers default_headers;

		static bool has_base_url();

		static void set_authorization_token(const std::string& token);

        static bool is_authorized();
	};
}
