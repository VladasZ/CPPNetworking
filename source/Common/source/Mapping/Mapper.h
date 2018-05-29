#pragma once

#include <string>
#include <functional>
#include <type_traits>

#include "ObjectResponse.h"
#include "ArrayResponse.h"

#include "Core.h"
#include "Config.h"

#include "Mappable.h"

namespace Rest
{
    template<class T> class Mappable;

	template<class T>
	struct Mapper
	{
        template<class T> friend class Mappable;

		using ArrayCompletion = std::function<void(const ArrayResponse<T>&)>;
		using ObjectCompletion = std::function<void(const ObjectResponse<T>&)>;

		static auto request(const std::string& url)
		{
			return [url](ObjectCompletion completion) { _request_object(url, "", completion); };
		};

		template<class Parameter>
		static auto request(const std::string& url)
		{
            return [url](Parameter parameter, ObjectCompletion completion)
            {
                _request_object(url + std::to_string(parameter), "", completion);
            };
		}

        template<>
        static auto request<std::string>(const std::string& url)
        {
            return [url](std::string parameter, ObjectCompletion completion)
            {
                _request_object(url + parameter, "", completion);
            };
        }

		static auto array_request(const std::string& url)
		{
			return [url](ArrayCompletion completion) { _request_array(url, "", completion); };
		}

	private:
		static void _request_array(const std::string& url, const std::string& body, const ArrayCompletion& completion)
		{
			Core::get_instance().http_request(url, HTTP::GET, body, [completion](const Response& response) {
				completion(ArrayResponse<T>(response));
			});
		}

		static void _request_object(const std::string& url, const std::string& body, const ObjectCompletion& completion)
		{
			Core::get_instance().http_request(url, HTTP::GET, body, [completion](const Response& response) {
				completion(ObjectResponse<T>(response));
			});
		}
	};
}
