#pragma once

#include "Poco/Exception.h"

#include "Response.h"

namespace Rest
{
	template<class T>
	class ObjectResponse : public Response
	{
	public:
		ObjectResponse(const Response& response)
			:
			Response(response)
		{
			if (has_error())
				return;

			try
			{
                auto json = JSON::parse(*body);
				object = T(json);
			}
			catch (const Poco::Exception& exception)
			{
				error = std::string("Failed to parse object: ") + typeid(T).name() + " Exception: " + exception.displayText();
			}
		}

		T object;
	};
}
