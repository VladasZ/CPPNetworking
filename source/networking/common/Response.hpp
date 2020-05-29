//
//  Response.hpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <functional>

#include "Request.hpp"


namespace net {
    
    class Response {

        Status _status;
        StatusCode _status_code;

        Body _body;

        Request _request;

    public:

        Error error;

        Response(const Request&, const Error& = no_error);
        Response(const Status&, StatusCode, const Body&, const Request&, const Error& = no_error);

        const Status& status() const;
        const StatusCode& status_code() const;

        const Body& body() const;

        const Request& request() const;

        std::string to_string() const;
    };
  
    using CoreCompletion = std::function<void(Response)>;

}
