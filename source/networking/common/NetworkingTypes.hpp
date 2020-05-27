//
//  NetworkingTypes.hpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <optional>
#include <functional>
#include <unordered_map>

#include "Path.hpp"


namespace net {

    using URL = cu::Path;
    using Body = std::string;
    using Error = std::optional<std::string>;
    using Status = std::string;
    using StatusCode = unsigned;

    inline constexpr auto no_error = std::nullopt;

    using Headers = std::unordered_map<std::string, std::string>;

    enum class Method {
        GET,
        POST
    };

    extern std::unordered_map<Method, std::string> method_to_string;
    extern std::unordered_map<std::string, Method> string_to_method;

    using Completion = std::function<void(Error)>;

    template <class T>
    using ObjectCompletion = std::function<void(Error, T)>;

}
