//
//  Response.hpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Request.hpp"


namespace net {
    
    class Response {
        
    public:
        
        const Error error;
        const Status status;
        const StatusCode status_code;
        
        const Body body;
        
        const Request request;
        
        Response(const Error&, const Request&);
        Response(const Error&, const Status&, StatusCode, const Body&, const Request&);
        
        std::string to_string() const;
    };
    
    using CoreCompletion = std::function<void(const Response&)>;

}
