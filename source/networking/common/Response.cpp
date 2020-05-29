//
//  Response.cpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Log.hpp"
#include "Response.hpp"

using namespace std;
using namespace net;


Response::Response(const Request& request, const Error& error)
: Response("", 0, "", request, error)
{ }

Response::Response(const Status& status,
                   StatusCode status_code,
                   const Body& body,
                   const Request& request,
                   const Error& error)
:
_status(status),
_status_code(status_code),
_body(body),
_request(request),
error(error)
{
    if (status_code > 299 && !error.has_value()) {
        this->error = std::to_string(status_code);
    }
}

const Status& Response::status() const {
    return _status;
}

const StatusCode& Response::status_code() const {
    return _status_code;
}

const Body& Response::body() const {
    return _body;
}

const Request& Response::request() const {
    return _request;
}

string Response::to_string() const {
    return string() +
    "Error: " + cu::Log::to_string(error) + "\n" +
    "Status: " + _status + "\n" +
    "Status code: " + ::to_string(_status_code) + "\n" +
    "Body: " + _body + "\n" +
    "Request:" + "\n" + _request.to_string();
}
