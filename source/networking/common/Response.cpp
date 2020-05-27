//
//  Response.cpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Response.hpp"

using namespace std;
using namespace net;


Response::Response(const Error& error, const Request& request)
: Response(error, "", 0, "", request)
{ }

Response::Response(const Error& error,
                   const Status& status,
                   StatusCode status_code,
                   const Body& body,
                   const Request& request)
:
_error(error),
_status(status),
_status_code(status_code),
_body(body),
_request(request)
{ }

const Error& Response::error() const {
    return _error;
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
    "Error: " + _error + "\n" +
    "Status: " + _status + "\n" +
    "Status code: " + ::to_string(_status_code) + "\n" +
    "Body: " + _body + "\n" +
    "Request:" + "\n" + _request.to_string();
}
