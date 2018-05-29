#pragma once

#include <memory>

#include "Poco/Exception.h"

#include "Response.h"

namespace Rest
{
	template<class T>
	class ArrayResponse : public Response
	{
	public:

        using ArrayPtr = std::shared_ptr<std::vector<T>>;

		ArrayResponse(const Response& response)
			:
			Response(response)
		{
			if (has_error())
				return;

			try
			{
				auto json = JSON::parse(*body);

				if (!json.isArray())
					return;

				array = T::map_to_array(json);
			}
			catch (const Poco::Exception& exception)
			{
				error = std::string("Failed to parse array: ") + typeid(T).name() + " Exception: " + exception.displayText();
			}
		}

        ArrayPtr array;
	};
}
