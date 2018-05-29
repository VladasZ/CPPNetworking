#pragma once

#include "Network.h"

using namespace std;
using namespace Rest;

Network::PlainRequest Network::request(const std::string& url)
{
    return [url](Completion completion) { _request(url, "", completion); };
}

Network::ParametrizedRequest Network::post_request(const std::string& url)
{
    return [url](const Parameters& parameters, Completion completion) { _request(url, JSONStruct(parameters).toString(), completion); };
}

void Network::_request(const std::string& url, const std::string& body, const Completion& completion)
{
    Core::get_instance().http_request(url, HTTP::GET, body, [completion](const Response& response) { completion(response); });
}