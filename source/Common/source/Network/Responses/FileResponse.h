#pragma once

#include "Response.h"

namespace Net
{
	class FileResponse : public Response
	{
	public:

        std::string file_name;

        FileResponse(const Response& response);
        FileResponse(const Response& response, const std::string file_name);
    private:
        void extract_file_name();
    };
}
