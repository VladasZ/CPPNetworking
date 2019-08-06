//
//  Client.hpp
//  networking
//
//  Created by Vladas Zakrevskis on 8/6/19.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <functional>
#include <unordered_map>

#include "Path.hpp"
#include "NetworkingTypes.hpp"

namespace net {
    
    class Client {
        
    public:
        
        cu::Path base_url;
        Headers headers;
        
        Client(const cu::Path& base_url);

        void request(const cu::Path&, Completion);
        void request(const cu::Path&, Method, Completion);
        
    };
}
