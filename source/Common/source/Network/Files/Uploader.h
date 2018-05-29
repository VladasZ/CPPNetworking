#pragma once

#include <string>
#include <functional>

#include "Poco\Net\HTMLForm.h"

#include "Response.h"
#include "Core.h"
#include "Mappable.h"

namespace Rest
{
	struct Uploader
	{
        template<class T>
        static void upload(const std::string& url, const T& object, const Response::Completion& completion)
        {
            Poco::Net::HTMLForm form;
            object.to_form(form);
            Core::get_instance().upload_request(url, form, completion);
        }
	};
}
