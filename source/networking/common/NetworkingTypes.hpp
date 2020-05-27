//
//  NetworkingTypes.hpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <unordered_map>

#include "Path.hpp"


namespace net {
    
    using URL        = cu::Path;
    using Body       = std::string;
    using Error      = std::string;
    using Status     = std::string;
    using StatusCode = unsigned;
    
    using Headers = std::unordered_map<std::string, std::string>;

    enum class Method {
        GET,
        POST
    };

    extern std::unordered_map<Method, std::string> method_to_string;
    extern std::unordered_map<std::string, Method> string_to_method;

}
