//
//  Request.hpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include "Path.hpp"
#include "NetworkingTypes.hpp"


namespace net {
    
    class Request {

        URL _url;
        Method _method;
        
    public:
        
        Request(const URL&, Method);

        const URL& url() const;
        Method method() const;
        
        std::string to_string() const;
    };

}
