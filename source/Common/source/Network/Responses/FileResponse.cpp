
#include "FileResponse.h"

using namespace std;
using namespace Net;

static string content_disposition_header = "Content-Disposition";

static string extract_string(const string& source, const string& start, const string& end)
{
    size_t startIndex = source.find(start);

    if (startIndex == std::string::npos)
        return "";

    startIndex += start.length();
    string::size_type endIndex = source.find(end, startIndex);
    return source.substr(startIndex, endIndex - startIndex);
}

FileResponse::FileResponse(const Response& response)
    :
    Response(response)
{
    if (has_error())
        return;

    extract_file_name();

    if (file_name.empty())
        error = "File name is empty.";
}

FileResponse::FileResponse(const Response& response, const string file_name)
    :
    Response(response)
{
    if (has_error())
        return;

    extract_file_name();

    if (!this->file_name.empty())
        return;

    this->file_name = file_name;

    if (file_name.empty())
        error = "File name is empty.";
}

void FileResponse::extract_file_name()
{
    string content_disposition = headers[content_disposition_header];
    file_name = extract_string(content_disposition, "filename=", ";");
}