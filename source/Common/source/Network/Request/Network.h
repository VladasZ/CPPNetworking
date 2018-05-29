#pragma once

#include <string>
#include <functional>

#include "Mapper.h"
#include "Core.h"
#include "Config.h"
#include "Downloader.h"
#include "Uploader.h"

namespace Rest
{
	struct Network
	{
		using Completion = std::function<void(const Response&)>;
        using PlainRequest = std::function<void(const Completion&)>;
        using ParametrizedRequest = std::function<void(const Parameters& parameters, const Completion&)>;

        static PlainRequest request(const std::string& url);
        static ParametrizedRequest post_request(const std::string& url);

	private:
        static void _request(const std::string& url, const std::string& body, const Completion& completion);
	};
}
