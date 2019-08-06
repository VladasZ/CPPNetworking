//
//  Response.cpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#include "Response.hpp"

using namespace net;
using namespace std;

Response::Response(const Error& error, const Request& request)
: Response(error, "", 0, "", request)
{ }

Response::Response(const Error& error,
                   const Status& status,
                   StatusCode status_code,
                   const Body& body,
                   const Request& request)
:
error(error),
status(status),
status_code(status_code),
body(body),
request(request)
{ }

string Response::to_string() const {
    return string() +
    "Error: " + error + "\n" +
    "Status: " + status + "\n" +
    "Status code: " + ::to_string(status_code) + "\n" +
    "Body: " + body + "\n" +
    "Request:" + "\n" + request.to_string();
}
