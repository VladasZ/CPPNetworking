#pragma once

#include <memory>
#include <functional>

#include "Poco\Dynamic\Var.h"

#include "HTTP.h"
#include "Mappable.h"

namespace Net
{
	class Response
	{
	public:

        using Completion = std::function<void(const Response&)>;

		Response() = default;
		Response(const Response& response);
		Response(const std::string& error);

		std::string request_url;
		HTTP::Method method;
        Headers requestHeaders;
		HTTP::ResponseCode response_code = 0;
		std::string error;
		std::shared_ptr<std::string> body = std::make_shared<std::string>("");
        Headers headers;

        std::string headersString() const;
        std::string requestHeadersString() const;

        bool has_error() const;
	};
}

std::ostream& operator<<(std::ostream& os, const Net::Response& obj);
