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

namespace net {

    using Error = std::string;
    using Headers = std::unordered_map<std::string, std::string>;

    using Completion = std::function<void(Error)>;

    enum class Method {
        GET,
        POST
    };

    extern const std::unordered_map<Method, std::string> method_to_string;
    extern const std::unordered_map<std::string, Method> string_to_method;

}
