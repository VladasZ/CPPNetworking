
#include "Response.h"

using namespace std;
using namespace Net;

static const bool print_headers = false;

Response::Response(const Response& response) 
	:
	request_url(response.request_url),
	method(response.method),
	response_code(response.response_code),
	error(response.error),
	body(response.body),
    headers(response.headers),
    requestHeaders(response.requestHeaders)
{

}

Response::Response(const string& error)
	:
	error(error)
{

}

string Response::headersString() const
{
    string result;

    for (const auto& header : headers)
        result += header.first + " : " + header.second + "\n";

    return result;
}

string Response::requestHeadersString() const
{
    string result;

    for (const auto& header : requestHeaders)
        result += header.first + " : " + header.second + "\n";

    return result;
}

bool Response::has_error() const
{
    return !error.empty();
}

ostream& operator<<(ostream& os, const Response& obj)
{
	auto bodyString = obj.body;

	if (!bodyString->empty() && bodyString->length() > 200)
		bodyString = make_shared<string>(bodyString->substr(0, 300));

    if (print_headers)
        return os << "url: " << obj.request_url << endl << endl <<
        "method: " << obj.method << endl << endl <<
        "request headers:" << endl << obj.requestHeadersString() << endl <<
        "status: " << obj.response_code << endl << endl <<
        "error: " << obj.error << endl << endl <<
        "response: " << *bodyString << endl << endl <<
        "response headers: " << endl << obj.headersString();

    return os << "url: " << obj.request_url << endl << endl <<
        "method: " << obj.method << endl << endl <<
        "status: " << obj.response_code << endl << endl <<
        "error: " << obj.error << endl << endl <<
        "response: " << *bodyString << endl;
}