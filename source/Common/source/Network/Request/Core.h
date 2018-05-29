#pragma once

#include <string>
#include <functional>

#include "Poco\Net\HTMLForm.h"

#include "Response.h"

namespace Rest
{
	struct Network;
    struct Uploader;
    struct Downloader;
	template<class T> class Mapper;

	class Core final
	{
		friend Network;
        friend Uploader;
        friend Downloader;
		template<class T> friend class Mapper;

        using Completion = std::function<void(const Response&)>;

        Core();
        ~Core();
		Core(const Core&) = delete;
		void operator=(const Core&) = delete;

		static Core& get_instance();
		void http_request(const std::string& url, const HTTP::Method& method, const std::string& body, Completion completion) const;
        void upload_request(const std::string& url, Poco::Net::HTMLForm& form, Completion completion) const;
	};
}
