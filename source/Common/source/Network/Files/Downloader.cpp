#pragma once

#include "Poco\File.h"
#include "Poco\FileStream.h"

#include "Downloader.h"
#include "Core.h"

using namespace Net;
using namespace std;
using namespace Poco;

void Downloader::download(
    const std::string& url, 
    const std::string& destination, 
    const FileDownloadCompletion& completion)
{
    download(url, destination, "", completion);
}

void Downloader::download(
    const std::string& url,
    const std::string& destination,
    const std::string& file_name,
    const FileDownloadCompletion& completion)
{
    Core::get_instance().http_request(url, HTTP::GET, "", [destination, file_name, completion](const Response& response) {
        FileResponse file_response(response, file_name);

        if (file_response.has_error())
        {
            completion(file_response);
            return;
        }

        string full_path =
            destination.empty() ?
            file_response.file_name :
            destination + "/" + file_response.file_name;

        File(destination).createDirectories();

        try
        {
            FileOutputStream fileStream(full_path);
            fileStream.write(file_response.body->c_str(), file_response.body->length());
            fileStream.close();
        }
        catch (const Exception& exception)
        {
            file_response.error = exception.displayText();
            completion(file_response);
            return;
        }

        completion(file_response);
    });
}
