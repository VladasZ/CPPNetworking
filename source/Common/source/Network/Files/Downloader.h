#pragma once

#include <string>
#include <functional>

#include "FileResponse.h"

namespace Rest
{
	struct Downloader
	{
        using FileDownloadCompletion = std::function<void(const FileResponse&)>;

        static void download(
            const std::string& url, 
            const std::string& destination, 
            const FileDownloadCompletion& completion
        );

        static void download(
            const std::string& url,
            const std::string& destination,
            const std::string& file_name,
            const FileDownloadCompletion& completion
        );
	};
}
