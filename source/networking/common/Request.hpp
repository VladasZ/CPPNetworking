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
        
    public:
        
        const URL url;
        const Method method;
        
        Request(const URL&, Method);
        
        std::string to_string() const;
    };

}
